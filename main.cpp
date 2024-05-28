#include "lz78.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


int main()
{
	// Test
	std::ifstream ifs("main.cpp");
	if (!ifs.is_open())
	{
		std::cerr << "Failed to open main.cpp file\n";
		return 1;
	}
	
	std::stringstream buffer;
	buffer << ifs.rdbuf();
	ifs.close();

	const std::string text_to_encode = buffer.str();
	const std::vector<std::pair<size_t, char>> dictionary = lz78Encode(text_to_encode);
	//printDictionary(dictionary);
	const std::string decoded_text = lz78Decoder(dictionary);
	
	std::ofstream ofs("decoded.cpp");
	if (!ofs.is_open())
	{
		std::cerr << "Failed to open decoded_main.cpp file\n";
		return 1;
	}

	ofs << decoded_text;
	ofs.close();

	return 0;
}


