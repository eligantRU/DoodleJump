#pragma once

#include "stdafx.h"
#include "sheet.h"

class FuckingJSONParser // NOT FOR RELEASE
{
public:
	std::string getArray(std::string str)
	{
		std::string arr = "";
		bool isArray = false;
		for (size_t i = 0; i < str.length(); ++i)
		{
			switch (str[i])
			{
			case '[':
				isArray = true;
				break;
			case ']':
				isArray = false;
				break;
			case '"':
				arr += str[i];
				++i;
				while (str[i] != '"')
				{
					arr += str[i];
					++i;
				}
				arr += str[i];
				break;
			default:
				arr += str[i];
				break;
			}
			if (!isArray)
			{
				break;
			}
		}
		arr += " ";
		return arr;
	}

	std::string getJSON(std::string & str)
	{
		std::string JSON = "";
		bool isJSON = false;
		for (size_t i = 0; i < str.length(); ++i)
		{
			switch (str[i])
			{
			case '{':
				isJSON = true;
				break;
			case '}':
				isJSON = false;
				++(++i);
				break;
			case '"':
				JSON += str[i];
				++i;
				while (str[i] != '"')
				{
					JSON += str[i];
					++i;
				}
				JSON += str[i];
				break;
			default:
				JSON += str[i];
				break;
			}
			if (!isJSON)
			{
				str = str.substr(i);
				break;
			}
		}
		return JSON;
	}

	std::string getkey(std::string str)
	{

	}

	std::string getValue(std::string str)
	{

	}

	std::string getCoupleKeyValue(std::string & str)
	{
		std::string inputStr = "";
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (str[i] == ',')
			{
				++i;
				str = str.substr(i);
				break;
			}
			if (i == str.length())
			{
				str = str.substr(i);
				break;
			}
			if (str[i] != '"')
			{
				inputStr += str[i];
			}
		}

		return inputStr;
	}

	std::map<std::string, std::string> getMap(std::string str)
	{
		std::string key = "";
		std::string value = "";

		for (size_t i = 0; i < str.length(); ++i)
		{
			if (str[i] == ':')
			{
				++i;
				for (size_t j = i; j < str.length(); ++j)
				{
					value += str[j];
				}
				break;
			}
			key += str[i];
		}
		std::map<std::string, std::string> result;
		result.insert(std::pair<std::string, std::string>(key, value));

		return result;
	}

	unsigned getArraySize(std::string str)
	{
		// How much time u can get new JSON = size
		// fuck, getJSON use substr, u must save your data :/
		return 0;
	}
};
