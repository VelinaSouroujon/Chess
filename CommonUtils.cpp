#include "commonUtils.h"

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

int CommonUtils::abs(int number)
{
	return number >= 0
		? number
		: -1 * number;
}
