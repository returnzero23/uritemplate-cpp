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

	};
private:
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