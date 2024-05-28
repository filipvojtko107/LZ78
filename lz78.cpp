#include "lz78.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cmath>


std::vector<std::pair<size_t, char>> lz78Encode(const std::string& text)
{
	std::vector<std::pair<size_t, char>> dictionary;
	std::vector<std::string> dict_texts;
	
	for (size_t i = 0; i < text.size(); ++i)
	{
		const char znak = text[i];
		std::string entry;
		entry.push_back(znak);
		auto found = std::find(dict_texts.begin(), dict_texts.end(), entry);
		
		// Nenalezeno
		if (found == dict_texts.end())
		{
			dictionary.emplace_back(0, znak);
			dict_texts.emplace_back(std::move(entry));
		}
		
		else
		{
			// Jedu dokud je text ulozen ve slovniku
			bool end = false;
			size_t dict_index = 0;
			auto current_found = dict_texts.begin();
			
			while ((current_found = std::find(dict_texts.begin() + dict_index, dict_texts.end(), entry)) != dict_texts.end())
			{
				found = current_found;
				i++;
				dict_index++;
				
				if (i >= text.size()) 
				{ 
					end = true;
					break;
				}
				
				else
				{
					entry.push_back(text[i]);
				}
			}
			
			const std::size_t found_index = std::distance(dict_texts.begin(), found) + 1;
			if (end)
			{
				dictionary.emplace_back(found_index, '\0');
			}
			
			else
			{
				dictionary.emplace_back(found_index, text[i]);
			}
		
			dict_texts.emplace_back(std::move(entry));
		}
	}
	
	return dictionary;
}


std::string lz78Decoder(const std::vector<std::pair<size_t, char>>& dictionary)
{
	std::string result;
	for (auto item = dictionary.begin(); item != dictionary.end(); ++item)
	{
		if (item->first == 0)
		{
			result.push_back(item->second);
		}
		
		else
		{
			std::string text;
			auto it = item;
			
			while (it->first != 0)
			{
				text.push_back(it->second);
				it = dictionary.begin() + (it->first - 1);
			}
			
			text.push_back(it->second);
			std::reverse(text.begin(), text.end());
			if (text.back() == '\0') { text.pop_back(); }		
			result += text;
		}
	}
	
	return result;
}


void printDictionary(const std::vector<std::pair<size_t, char>>& d)
{
	std::cout << "Dictionary: \n";
	for (const auto& item : d)
	{
		std::cout << '<' << item.first << "; " << item.second << ">\n";
	}
	
	std::cout << '\n';
}
