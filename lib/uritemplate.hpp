#ifndef URITEMPLATECPP_H
#define URITEMPLATECPP_H

#include <string>
#include <vector>
#include <map>

namespace uritemplatecpp{

enum VarSpecType {
    Raw = 0,
    Prefixed,
    Exploded
};

struct VarSpec {
    std::string name;
    VarSpecType var_type;
};

enum Operator{
    Null,
    Plus,
    Dot,
    Slash,
    Semi,
    Question,
    Ampersand,
    Hash
};

struct TemplateComponent{
    std::string literal;
    std::pair< Operator, std::vector<VarSpec> >  varList;
public:
	TemplateComponent(const std::string inLiteral){
		literal = inLiteral;
	};

	TemplateComponent(const std::pair< Operator, std::vector<VarSpec> >  inVarList){
		varList = inVarList;
	};
};

class TemplateVar{
public:
	TemplateVar(const std::string varBuf){
		if(varBuf[0] == '['){
			list = parseVarVector(varBuf);
			type = List;
		}else if(varBuf[0] == '{'){
			associativeArray = parseVarAssociativeArray(varBuf);
			type = AssociativeArray;
		}else{
			scalar = varBuf;
			type = Scalar;
		}
	};
private:
	std::vector<std::string> parseVarVector(std::string inBuf){
		using string = std::string;
		std::vector<string> result;
		bool in_varlist = false;
		string buf;
		for(string::iterator ch = inBuf.begin() + 1; ch != inBuf.end(); ch++)
		{
			if(in_varlist && *ch == '"'){
				in_varlist = false;
				if( buf.size() > 0 )
					result.push_back(buf);
				buf.clear();
				continue;
			}

			if(!in_varlist && *ch == '"'){
				buf.push_back(*ch);
				in_varlist = true;
				buf.push_back(*ch);
				continue;
			}
		}
		return result;
	}

	std::vector< std::pair< std::string, std::string > > parseVarAssociativeArray(std::string inBuf){
		using string = std::string;
		std::vector<std::pair< std::string, std::string > > result;
		bool in_varlist = false;
		bool isKey = true;
		string buf;
		string key, value;
		for(string::iterator ch = inBuf.begin() + 1; ch != inBuf.end(); ch++)
		{
			if(in_varlist && *ch == '"'){
				in_varlist = false;
				if( buf.size() > 0 ){
					if(isKey){
						key = buf;
						isKey = false;
					}else{
						value = buf;
						isKey = true;
						result.push_back(std::pair<string,string>(key,value));
						key.clear();
						value.clear();
					}
				}
				buf.clear();
				continue;
			}

			if(!in_varlist && *ch == '"'){
				buf.push_back(*ch);
				in_varlist = true;
				buf.push_back(*ch);
				continue;
			}
		}
		return std::vector< std::pair< std::string, std::string > >();
	}
	
private:
	enum Type {
		Null = -1,
		Scalar,
		List,
		AssociativeArray,
	};
	Type type;
    std::string scalar;
    std::vector<std::string> list;
    std::vector< std::pair< std::string, std::string > > associativeArray;
};

class UriTemplate{
public:
	UriTemplate(std::string src_template){
		using string = std::string;
		bool in_varlist = false;
		string buf;
		for(string::iterator ch = src_template.begin(); ch != src_template.end(); ch++)
		{
			if(in_varlist && *ch == '}'){
				components.push_back(parse_varlist(buf));
				buf.clear();
				in_varlist = false;
				continue;
			}

			if(in_varlist && *ch == '{'){
				if( buf.size() > 0 ){
					components.push_back(TemplateComponent(buf));
					buf.clear();
				}
				components.push_back(parse_varlist(buf));
				buf.clear();
				in_varlist = false;
				continue;
			}
		}

		if( buf.size() > 0 ){
			components.push_back(TemplateComponent(buf));
		}
	};

	std::string expand(std::map<std::string,std::string> inVars){
		//vars = inVars;
		return std::string();
	};

	std::string expand(std::string key, std::string val){
		vars.insert(std::pair<std::string,TemplateVar>(key,TemplateVar(val)));
		return std::string();
	}
private:
	TemplateComponent parse_varlist(std::string){
		return TemplateComponent(std::string());
	}
private:
    std::vector<TemplateComponent> components;
    std::map<std::string,TemplateVar> vars;
};

}//uritemplatecpp end 
#endif //URITEMPLATECPP_H end