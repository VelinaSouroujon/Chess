#pragma once

#include <iostream>
#include <utility>

namespace CommonUtils
{
	char toLower(char ch);
	char toUpper(char ch);
	int strCompareCaseInsensitive(const char* str1, const char* str2);
	bool isInRange(int value, int from, int to);
	bool isLetter(char ch);
	int getMax(int firstNum, int secondNum);
	int getMin(int firstNum, int secondNum);
	int abs(int number);
	void clearConsole();
	int readNumber(std::ostream& os, std::istream& is);
	int getNumberInRange(std::ostream& os, std::istream& is, int from, int to);

	template <typename T>
	void swap(T& first, T& second)
	{
		if (&first == &second)
		{
			return;
		}

		T temp = std::move(first);
		first = std::move(second);
		second = std::move(temp);
	}
};

