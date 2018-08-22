#include <string>
#include <fstream>
#include <iostream>

#include "../lib/uritemplate.hpp"
#include "../ext/json/include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;
using UriTemplate = uritemplatecpp::UriTemplate;

class LevelTestCase{
public:
	void setVectorVariables(const std::string key, const std::vector<std::string>& vars){
		variables.insert(std::pair<std::string,VarType>(key,VarType(vars)));
	};

	void setMapVariables(const std::string key, const std::map<std::string, std::string>& vars){
		variables.insert(std::pair<std::string,VarType>(key,VarType(vars)));
	};
public:
	struct VarType{
		enum Type {
			Null = -1,
			Scalar,
			Vec,
			Map,
		};
		Type type;
		std::map<std::string, std::string> mapVars;
		std::vector<std::string> vecVars;
		std::string scalarVar;
	public:
		VarType(const std::map<std::string, std::string>& var){
			type = Map;
			mapVars = var;
		};
		VarType(const std::vector< std::string > var){
			type = Vec;
			vecVars = var;
		};
		VarType(const std::string var){
			type = Scalar;
			scalarVar = var;
		}
	};
	uint level;
	std::map<std::string,VarType> variables;
	std::map<std::string,std::string> variablesString;

	std::vector< std::pair<string,string> > testcases;
};

bool parseTestCase(const json& parseJson, LevelTestCase& result){
	
	try
	{
		result.level = parseJson["level"];

		json Jvariables = parseJson["variables"];
		for(json::iterator it = Jvariables.begin(); it != Jvariables.end(); ++it)
		{
			// if(it.value().is_array()){
			// 	//todo
			// }else if(it.value().is_object()){
			// 	//todo
			// }else{
			// 	result.variables.insert(std::pair<string,LevelTestCase::VarType>(it.key(),LevelTestCase::VarType(it.value().get<string>())));
			// }
			result.variables.insert(std::pair<string,LevelTestCase::VarType>(it.key(),LevelTestCase::VarType(it.value().dump())));
		}

		json JtestCases = parseJson["testcases"];
		for(json::iterator it = JtestCases.begin(); it != JtestCases.end(); ++it)
		{
			if(it->at(1).is_array()){
				//std::cout << "array" << std::endl;
				//todo
			}else{
				result.testcases.push_back(std::make_pair<string,string>(it->at(0).get<string>(),it->at(1).get<string>()));
			}
		}
		return true;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return false;
};

int main(int argc, char* argv[]){
	// for (int i = 0; i<argc; i++)
    //     std::cout << argv[i] << std::endl;

	string filePath = argv[1];

	std::ifstream i(filePath);
	json j;
	
	try
	{
		i >> j;
		//std::cout << j << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "json parse error ! the error is " <<e.what() << '\n';
		exit(1);
	}

	json Level1Test = j["Level 2 Examples"];
	LevelTestCase level1Case;
	if(parseTestCase(Level1Test,level1Case)){
		for(std::pair<string,string> element : level1Case.testcases){
			UriTemplate uri(std::get<0>(element));
			std::map<std::string,std::string> varMap;
			for(auto& ele : level1Case.variables){
				varMap.insert(std::pair<std::string,std::string>(ele.first,ele.second.scalarVar.substr(1,ele.second.scalarVar.size()-2)));
			}
			if(std::get<1>(element) == uri.expand(varMap)){
				std::cout << "pass" ;
			}else{
				std::cout << "failed" ;
			}
			std::cout << std::endl;

			// for(auto& ele : level1Case.variables){
			// 	if(ele.second.type == LevelTestCase::VarType::Vec){
			// 		if(std::get<1>(element) == uri.expand(ele.first, ele.second.vecVars)){
			// 			std::cout << "pass" ;
			// 		}else{
			// 			std::cout << "failed" ;
			// 		}
			// 		std::cout << std::endl;
			// 	}else if (ele.second.type == LevelTestCase::VarType::Map){
			// 		if(std::get<1>(element) == uri.expand(ele.second.mapVars)){
			// 			std::cout << "pass" ;
			// 		}else{
			// 			std::cout << "failed" ;
			// 		}
			// 		std::cout << std::endl;
			// 	}else{
 			// 		if(std::get<1>(element) == uri.expand(ele.first, ele.second.scalarVar.substr(1,ele.second.scalarVar.size()-2))){
			// 			std::cout << "pass" ;
			// 		}else{
			// 			std::cout << "failed" ;
			// 		}
			// 		std::cout << std::endl;
			// 	}
			// }
		}
	}



    return 0;
}