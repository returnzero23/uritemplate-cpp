#include <string>
#include <fstream>
#include <iostream>

#include "../lib/uritemplate.hpp"
#include "../ext/json/include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;
using UriTemplate = uritemplatecpp::UriTemplate;

class TestCase{
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

	std::vector< std::pair<std::string,std::vector<std::string> > > testcases;
};

bool parseTestCase(const json& parseJson, TestCase& result){
	
	try
	{
		json Jvariables = parseJson["variables"];
		for(json::iterator it = Jvariables.begin(); it != Jvariables.end(); ++it)
		{
			if(it.value().is_null()){
				// null means undefined, therefore no variable to "define" here
				continue;
			}else if(it.value().is_array()){
				std::vector<std::string> listStr;
				for(json::iterator it2 = it->begin(); it2 != it->end(); ++it2)
				{
					listStr.push_back(it2->get<std::string>());
				}
				result.setVectorVariables(it.key(),listStr);
			}else if(it.value().is_object()){
				std::map<std::string,std::string> mapStr;
				for(json::iterator it2 = it->begin(); it2 != it->end(); ++it2)
				{
					mapStr.insert(std::pair<std::string,std::string>(it2.key(),it2.value().get<std::string>()));
				}
				result.setMapVariables(it.key(),mapStr);
			}else{
				result.variables.insert(std::pair<string,TestCase::VarType>(it.key(),TestCase::VarType(it.value().get<string>())));
			}
		}

		json JtestCases = parseJson["testcases"];
		for(json::iterator it = JtestCases.begin(); it != JtestCases.end(); ++it)
		{
			std::vector<std::string> resultList;
			if(it->at(1).is_array()){
				for(json::iterator it2 = it->at(1).begin(); it2 != it->at(1).end(); ++it2){
					resultList.push_back(it2->get<std::string>());
				}
			}else{
				resultList.push_back(it->at(1).get<std::string>());
			}
			result.testcases.push_back(std::pair<std::string,std::vector<std::string> >(it->at(0).get<string>(),resultList));
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

	string filePath = argv[1];

	std::ifstream i(filePath);
	json j;
	
	try
	{
		i >> j;
	}
	catch(const std::exception& e)
	{
		std::cerr << "json parse error ! the error is " <<e.what() << '\n';
		exit(1);
	}

	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		std::cout << "Run test \"" << it.key() << "\"\n";
		json testData = j[it.key()];
		TestCase testCase;
		if(parseTestCase(testData,testCase)){
			for(std::pair<string,std::vector<string> > element : testCase.testcases){
				UriTemplate uri(std::get<0>(element));
				std::map<std::string,std::string> varMap;
				for(auto& ele : testCase.variables){
					
					switch (ele.second.type)
					{
						case TestCase::VarType::Type::Scalar:
							uri.set(ele.first,ele.second.scalarVar);
							break;
						case TestCase::VarType::Type::Map:
							uri.set(ele.first,ele.second.mapVars);
							break;
						case TestCase::VarType::Type::Vec:
							uri.set(ele.first,ele.second.vecVars);
							break;
					
						default:
							break;
					}
				}

				bool pass = false;
				std::string result = uri.build();
				for(auto& ele :std::get<1>(element))
				{
					if(ele == result){
						pass = true;
					}
				}
				
				if(pass){
					std::cout << "pass" ;
				}else{
					std::cout << "failed" ;
				}
				std::cout << std::endl;
			}
		}
	}

	



    return 0;
}
