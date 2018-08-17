#include <string>
#include <fstream>
#include <iostream>

#include "../lib/uritemplate.hpp"
#include "../ext/json/include/nlohmann/json.hpp"

using json = nlohmann::json;
using std::string;

struct LevelTestCase{
	uint level;
	std::map<std::string,std::string> variables;
	std::vector< std::pair<string,string> > testcases;
};

bool parseTestCase(const json& parseJson, LevelTestCase& result){
	result.level = parseJson["level"];
	
	json Jvariables = parseJson["variables"];
	for(json::iterator it = Jvariables.begin(); it != Jvariables.end(); ++it)
	{
		result.variables.insert(it.key(),it.value().get<string>());
	}

	json JtestCases = parseJson["testcases"];
	for(json::iterator it = Jvariables.begin(); it != Jvariables.end(); ++it)
	{
		result.testcases.push_back(std::pair<string,string>(it[0].get<string>(),it[1].get<string>()));
	}
};

int main(int argc, char* argv[]){
	for (int i = 0; i<argc; i++)
        std::cout << argv[i] << std::endl;

	string filePath = argv[1];

	std::ifstream i(filePath);
	json j;
	
	try
	{
		i >> j;
		std::cout << j << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "json parse error ! the error is " <<e.what() << '\n';
		exit(1);
	}

	json Level1Test = j["Level 1 Examples"];
	LevelTestCase level1Case;
	parseTestCase(Level1Test,level1Case);
	
    return 0;
}