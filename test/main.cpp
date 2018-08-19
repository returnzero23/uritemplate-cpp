#include <string>
#include <fstream>
#include <iostream>

#include "../lib/uritemplate.hpp"
#include "../ext/json/include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;
using UriTemplate = uritemplatecpp::UriTemplate;

struct LevelTestCase{
	uint level;
	std::map<std::string,std::string> variables;
	std::vector< std::pair<string,string> > testcases;
};

bool parseTestCase(const json& parseJson, LevelTestCase& result){
	
	try
	{
		result.level = parseJson["level"];

		json Jvariables = parseJson["variables"];
		for(json::iterator it = Jvariables.begin(); it != Jvariables.end(); ++it)
		{
			if(it.value().is_array()){
				//todo
			}else if(it.value().is_object()){
				//todo
			}else{
				result.variables.insert(std::pair<string,string>(it.key(),it.value().get<string>()));
			}
		}

		json JtestCases = parseJson["testcases"];
		for(json::iterator it = JtestCases.begin(); it != JtestCases.end(); ++it)
		{
			if(it->at(1).is_array()){
				//std::cout << "array" << std::endl;
				//todo
			}else{
				std::cout << "string" << std::endl;
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

	json Level1Test = j["Level 4 Examples"];
	LevelTestCase level1Case;
	if(parseTestCase(Level1Test,level1Case)){
		for(std::pair<string,string> element : level1Case.testcases){
			UriTemplate uri(std::get<0>(element));
			if(std::get<1>(element) == uri.expand(level1Case.variables)){
				std::cout << "pass" ;
			}else{
				std::cout << "failed" ;
			}
			std::cout << std::endl;
		}
	}



    return 0;
}