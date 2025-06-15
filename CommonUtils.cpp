#define NOMINMAX
#include <stdexcept>
#include <limits>
#include <Windows.h>
#include "CommonUtils.h"

char CommonUtils::toLower(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
	{
		return ch + ('a' - 'A');
	}

	return ch;
}

char CommonUtils::toUpper(char ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		return ch + ('A' - 'a');
	}

	return ch;
}

int CommonUtils::strCompareCaseInsensitive(const char* str1, const char* str2)
{
	if (str1 == nullptr || str2 == nullptr)
	{
		throw std::invalid_argument("Argument cannot be null.");
	}

	int result = 0;
	int idx = 0;

	while (true)
	{
		char firstChar = toLower(str1[idx]);
		char secondChar = toLower(str2[idx]);

		if (firstChar < secondChar)
		{
			result = -1;
			break;
		}

		if (secondChar < firstChar)
		{
			result = 1;
			break;
		}

		if (firstChar == '\0')
		{
			break;
		}

		idx++;
	}

	return result;
}

bool CommonUtils::isInRange(int value, int from, int to)
{
	return value >= from
		&& value <= to;
}

bool CommonUtils::isLetter(char ch)
{
	return isInRange(ch, 'a', 'z')
		|| isInRange(ch, 'A', 'Z');
}

int CommonUtils::getMax(int firstNum, int secondNum)
{
	return firstNum < secondNum
		? secondNum
		: firstNum;
}

int CommonUtils::getMin(int firstNum, int secondNum)
{
	return firstNum < secondNum
		? firstNum
		: secondNum;
}

int CommonUtils::abs(int number)
{
	return number >= 0
		? number
		: -1 * number;
}

void CommonUtils::clearConsole()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		cellCount = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
		SetConsoleCursorPosition(hConsole, homeCoords);
	}
}

int CommonUtils::readNumber(std::ostream& os, std::istream& is)
{
	if (!os.good())
	{
		throw std::runtime_error("Output stream file not in good state");
	}
	if (!is.good())
	{
		throw std::runtime_error("Input stream file not in good state");
	}

	int num;
	is >> num;

	while (is.fail())
	{
		os << "Invalid input! Please enter a number." << std::endl;
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		is >> num;
	}

	return num;
}

int CommonUtils::getNumberInRange(std::ostream& os, std::istream& is, int from, int to)
{
	int num = readNumber(os, is);

	while (!CommonUtils::isInRange(num, from, to))
	{
		os << "Invalid number! Please enter a number between " << from << " and " << to << std::endl;
		num = readNumber(os, is);
	}

	return num;
}
