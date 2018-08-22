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

struct VarSpec {
    std::string name;
    VarSpecType var_type;
	unsigned int size;
public:
	VarSpec(std::string name,VarSpecType type,unsigned int size = 0):
		name(name),
		var_type(type),
		size(size)
	{}
};

const std::string UNRESERVED[] = {
   "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07",
   "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F",
   "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17",
   "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F",
   "%20", "%21", "%22", "%23", "%24", "%25", "%26", "%27",
   "%28", "%29", "%2A", "%2B", "%2C", "-", ".", "%2F",
   "0", "1", "2", "3", "4", "5", "6", "7",
   "8", "9", "%3A", "%3B", "%3C", "%3D", "%3E", "%3F",
   "%40", "A", "B", "C", "D", "E", "F", "G",
   "H", "I", "J", "K", "L", "M", "N", "O",
   "P", "Q", "R", "S", "T", "U", "V", "W",
   "X", "Y", "Z", "%5B", "%5C", "%5D", "%5E", "_",
   "%60", "a", "b", "c", "d", "e", "f", "g",
   "h", "i", "j", "k", "l", "m", "n", "o",
   "p", "q", "r", "s", "t", "u", "v", "w",
   "x", "y", "z", "%7B", "%7C", "%7D", "~", "%7F",
   "%80", "%81", "%82", "%83", "%84", "%85", "%86", "%87",
   "%88", "%89", "%8A", "%8B", "%8C", "%8D", "%8E", "%8F",
   "%90", "%91", "%92", "%93", "%94", "%95", "%96", "%97",
   "%98", "%99", "%9A", "%9B", "%9C", "%9D", "%9E", "%9F",
   "%A0", "%A1", "%A2", "%A3", "%A4", "%A5", "%A6", "%A7",
   "%A8", "%A9", "%AA", "%AB", "%AC", "%AD", "%AE", "%AF",
   "%B0", "%B1", "%B2", "%B3", "%B4", "%B5", "%B6", "%B7",
   "%B8", "%B9", "%BA", "%BB", "%BC", "%BD", "%BE", "%BF",
   "%C0", "%C1", "%C2", "%C3", "%C4", "%C5", "%C6", "%C7",
   "%C8", "%C9", "%CA", "%CB", "%CC", "%CD", "%CE", "%CF",
   "%D0", "%D1", "%D2", "%D3", "%D4", "%D5", "%D6", "%D7",
   "%D8", "%D9", "%DA", "%DB", "%DC", "%DD", "%DE", "%DF",
   "%E0", "%E1", "%E2", "%E3", "%E4", "%E5", "%E6", "%E7",
   "%E8", "%E9", "%EA", "%EB", "%EC", "%ED", "%EE", "%EF",
   "%F0", "%F1", "%F2", "%F3", "%F4", "%F5", "%F6", "%F7",
   "%F8", "%F9", "%FA", "%FB", "%FC", "%FD", "%FE", "%FF",
};

const std::string RESERVED[] = {
   "%00", "%01", "%02", "%03", "%04", "%05", "%06", "%07",
   "%08", "%09", "%0A", "%0B", "%0C", "%0D", "%0E", "%0F",
   "%10", "%11", "%12", "%13", "%14", "%15", "%16", "%17",
   "%18", "%19", "%1A", "%1B", "%1C", "%1D", "%1E", "%1F",
   "%20", "!", "%22", "#", "$", "%25", "&", "'",
   "(", ")", "*", "+", ",", "-", ".", "/",
   "0", "1", "2", "3", "4", "5", "6", "7",
   "8", "9", ":", ";", "%3C", "=", "%3E", "?",
   "@", "A", "B", "C", "D", "E", "F", "G",
   "H", "I", "J", "K", "L", "M", "N", "O",
   "P", "Q", "R", "S", "T", "U", "V", "W",
   "X", "Y", "Z", "[", "%5C", "]", "%5E", "_",
   "%60", "a", "b", "c", "d", "e", "f", "g",
   "h", "i", "j", "k", "l", "m", "n", "o",
   "p", "q", "r", "s", "t", "u", "v", "w",
   "x", "y", "z", "%7B", "%7C", "%7D", "~", "%7F",
   "%80", "%81", "%82", "%83", "%84", "%85", "%86", "%87",
   "%88", "%89", "%8A", "%8B", "%8C", "%8D", "%8E", "%8F",
   "%90", "%91", "%92", "%93", "%94", "%95", "%96", "%97",
   "%98", "%99", "%9A", "%9B", "%9C", "%9D", "%9E", "%9F",
   "%A0", "%A1", "%A2", "%A3", "%A4", "%A5", "%A6", "%A7",
   "%A8", "%A9", "%AA", "%AB", "%AC", "%AD", "%AE", "%AF",
   "%B0", "%B1", "%B2", "%B3", "%B4", "%B5", "%B6", "%B7",
   "%B8", "%B9", "%BA", "%BB", "%BC", "%BD", "%BE", "%BF",
   "%C0", "%C1", "%C2", "%C3", "%C4", "%C5", "%C6", "%C7",
   "%C8", "%C9", "%CA", "%CB", "%CC", "%CD", "%CE", "%CF",
   "%D0", "%D1", "%D2", "%D3", "%D4", "%D5", "%D6", "%D7",
   "%D8", "%D9", "%DA", "%DB", "%DC", "%DD", "%DE", "%DF",
   "%E0", "%E1", "%E2", "%E3", "%E4", "%E5", "%E6", "%E7",
   "%E8", "%E9", "%EA", "%EB", "%EC", "%ED", "%EE", "%EF",
   "%F0", "%F1", "%F2", "%F3", "%F4", "%F5", "%F6", "%F7",
   "%F8", "%F9", "%FA", "%FB", "%FC", "%FD", "%FE", "%FF",
};

std::string encode_unreserved(std::string encodeStr){
	std::vector<std::string> vecStr;
	vecStr.resize(encodeStr.size());
	for (int i = 0; i < encodeStr.size(); i++){
		vecStr[i] = UNRESERVED[(int)encodeStr[i]];
	}
	std::string result;
	
	for(auto& ele : vecStr)
	{
		result += ele; 
	}
	return result;
}

std::string encode_reserved(const std::string encodeStr){
	std::vector<std::string> vecStr;
	vecStr.resize(encodeStr.size());
	for (int i = 0; i < encodeStr.size(); i++){
		vecStr[i] = RESERVED[(int)encodeStr[i]];
	}
	std::string result;
	
	for(auto& ele : vecStr)
	{
		result += ele; 
	}
	return result;
}

struct TemplateComponent{
	TemplateComponent(const std::string inLiteral){
		literal = inLiteral;
		type = Literal;
	};

	TemplateComponent(const std::pair< Operator, std::vector<VarSpec> >  inVarList){
		varList = inVarList;
		type = VarList;
	};

	enum Type {
		Literal = 0,
		VarList,
	};
	Type type;
    std::string literal;
    std::pair< Operator, std::vector<VarSpec> >  varList;
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

	TemplateVar(const std::vector<std::string> vecVars){
		list = vecVars;
		type = List;
	};

	TemplateVar(const std::vector< std::pair< std::string, std::string > > mapVars){
		associativeArray = mapVars;
		type = AssociativeArray;
	}
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
		return result;
	}
public:
	enum Type {
		Null = -1,
		Scalar,
		List,
		AssociativeArray,
	};
	Type type = Null;
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

			if(!in_varlist && *ch == '{'){
				if( buf.size() > 0 ){
					components.push_back(TemplateComponent(buf));
					buf.clear();
				}
				buf.clear();
				in_varlist = true;
				continue;
			}

			buf.push_back(*ch);
		}

		if( buf.size() > 0 ){
			components.push_back(TemplateComponent(buf));
		}
	};

	std::string expand(const std::string key, const std::vector<std::string> inVars){
		//todo
		return std::string();
	};

	std::string expand(const std::map<std::string,std::string> inVars){
		for(auto& ele : inVars)
		{
			//std::cout << ele.first << ":" << ele.second << std::endl;
			vars.insert(std::pair<std::string,TemplateVar>(ele.first,TemplateVar(ele.second)));
		}
		
		std::string result;
		for(auto& ele : components)
		{
			switch(ele.type){
				case TemplateComponent::Literal: result = encode_reserved(ele.literal);break;
				case TemplateComponent::VarList: result = build_varlist(ele.varList);break;
			}
		}
		std::cout << result << std::endl;
		return result;
	};

	std::string expand(const std::string key, std::string val){
		vars.insert(std::pair<std::string,TemplateVar>(key,TemplateVar(val)));
		std::string result;

		for(auto& ele : components)
		{
			switch(ele.type){
				case TemplateComponent::Literal: result = encode_reserved(ele.literal);break;
				case TemplateComponent::VarList: result = build_varlist(ele.varList);break;
			}
		}
		return result;
	};

	std::string expand(const std::string varSrc){
		//todo
		return std::string();
	};
private:
	TemplateComponent parse_varlist(std::string src){
		assert(src.size() > 0);
		Operator componentOperator;
		switch(src[0]){
			case '+': componentOperator = Plus; break;
			case '.': componentOperator = Dot; break;
			case '/': componentOperator = Slash; break;
			case ';': componentOperator = Plus; break;
			case '?': componentOperator = Question; break;
			case '&': componentOperator = Ampersand; break;
			case '#': componentOperator = Hash; break;
			default:  componentOperator = Null;
		}
		if(componentOperator != Null){
			src = src.substr(1);
		}
		std::vector<std::string> stringList;
		std::vector<VarSpec> specList;
		if(string2vector(src,",",stringList)){
			for(auto& ele : stringList)
			{				
				if(ele.size() > 2 && ele[-1] == '*'){
					specList.push_back(VarSpec(ele.substr(0, ele.size() - 1),Exploded));
				}else if(ele.find(':') != std::string::npos){
					std::string::size_type pos = ele.find(':');
					unsigned int size;
					sscanf(ele.substr(pos+1).c_str(),"%d",&size);
					specList.push_back(VarSpec(ele.substr(0, pos),Prefixed,size));
				}else{
					specList.push_back(VarSpec(ele,Raw,0));
				}
			}
		}
		return TemplateComponent(std::pair< Operator, std::vector<VarSpec> >(componentOperator,specList));
	};

	bool string2vector(const std::string& srcString, const std::string& splitChar, std::vector<std::string>& result){
		std::string::size_type pos1, pos2;
		pos2 = srcString.find(splitChar);
		pos1 = 0;
		while(std::string::npos != pos2)
		{
			result.push_back(srcString.substr(pos1, pos2-pos1));
			pos1 = pos2 + splitChar.size();
			pos2 = srcString.find(splitChar, pos1);
		}
		if(pos1 != srcString.length())
			result.push_back(srcString.substr(pos1));

		return result.size() > 0;
	};

	std::string encode_reserved(const std::string& str){
		for(auto& achar : str){

		}
		return str;
	};

	std::string build_varlist(const  std::pair< Operator, std::vector<VarSpec> > varList){
		struct BuildSpecParm {
			std::string varspec;
			std::string sep;
			bool named;
			std::string ifemp;
			bool encode_reserved;
		BuildSpecParm(std::string varspec, std::string sep,	bool named,	std::string ifemp, bool encode_reserved):
			varspec(varspec),
			sep(sep),
			named(named),
			ifemp(ifemp),
			encode_reserved(encode_reserved)
			{};

		BuildSpecParm(){
		};

		};
		BuildSpecParm buildSpecParm;
		switch(varList.first){
			case Null:
				buildSpecParm = BuildSpecParm("",",",false,"",false);
			break;
			case Plus:
				buildSpecParm = BuildSpecParm("",",",false,"",true);
			break;
			case Dot:
				buildSpecParm = BuildSpecParm(".",".",false,"",false);
			break;
			case Slash:
				buildSpecParm = BuildSpecParm("/","/",false,"",false);
			break;
			case Semi:
				buildSpecParm = BuildSpecParm(";",";",false,"",false);
			break;
			case Question:
				buildSpecParm = BuildSpecParm("?","&",false,"=",false);
			break;
			case Ampersand:
				buildSpecParm = BuildSpecParm("&","&",false,"=",false);
			break;
			case Hash:
				buildSpecParm = BuildSpecParm("#",",",false,"",true);
			break;
			default:;
		}
		std::string result;
		for(auto varSpec : varList.second){
			bool isPrefixed = false;
			bool isExploded = false;
			switch(varSpec.var_type){
				case Prefixed: isPrefixed = true; break;
				case Exploded: isExploded = true; break;
				case Raw:break;
				default:;
			};
			if(vars.find(varSpec.name) != vars.end()){
				std::string fixedString;
				if(isPrefixed){
					vars.at(varSpec.name).scalar.resize(varSpec.size);
				}
				fixedString = vars.at(varSpec.name).scalar;
				if(isExploded){
					result += encode_reserved(fixedString);
				}else{
					result += encode_unreserved(fixedString);
				}
				std::cout << isExploded << result << std::endl;
			}
		}
		return result;
	};
private:
    std::vector<TemplateComponent> components;
    std::map<std::string,TemplateVar> vars;
};

}//uritemplatecpp end 
#endif //URITEMPLATECPP_H end