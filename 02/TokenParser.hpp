#pragma once
#include <iostream>
#include <functional>
#include <string>

class TokenParser
{
	private:
		std::function<void()> StartCallback;
	//	std::function<void()> EndCallback;
	//	std::function<void(uint64_t)> DigitTokenCallback;
	//	std::function<void(const std::string&)> StringTokenCallback;
	public:
		TokenParser() = default;
		void SetStartCallback(std::function<void()> f = nullptr);
	//	void SetEndCallback(std::function<void()> f){};

	//	void SetDigitTokenCallback(std::function<void(uint64_t)> f = nullptr){};

	//	void SetStringokenCallback(std::function<void(const std::string&)> f = nullptr){};

		void Parse(const std::string& line) const;
		
};
