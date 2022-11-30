#include "TokenParser.hpp"
#include <iostream>

void TokenParser::SetStartCallback(std::function<void()> f)
{
	StartCallback = f ? f :[] {};
}

void TokenParser::SetEndCallback(std::function<void()> f)
{
        EndCallback = f ? f :[] {};
}

void TokenParser::SetDigitTokenCallback(std::function<void(uint64_t)> f)

{
        DigitTokenCallback = f ? f :[](uint64_t) {};
}

void TokenParser::SetStringTokenCallback(std::function<void(const std::string&)> f)
{
        StringTokenCallback = f ? f :[](const std::string&) {};
}



void TokenParser::Parse(const std::string& line) const
{
	std::cout << line << std::endl;
}
