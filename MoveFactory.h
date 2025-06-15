#pragma once

#include "Move.h"

class MoveFactory
{
public:
	static Move* createMove(const char* notation);
};

