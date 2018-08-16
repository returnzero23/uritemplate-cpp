#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "../lib/uritemplate.hpp"
#include "../ext/json/include/nlohmann/json.hpp"


using json = nlohmann::json;
using std::string;

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
		std::cerr << e.what() << '\n';
	}

	system("pause");
    return 0;
}