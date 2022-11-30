#include "TokenParser.hpp"
#include <iostream>

void TokenParser::SetStartCallback(std::function<void()> f)
{
	StartCallback = f ? f : {};
}

void TokenParser::Parse(const std::string& line) const
{
	std::cout << line << std::endl;
}
