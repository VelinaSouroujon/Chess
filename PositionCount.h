#pragma once

#include "StringGameSerializer.h"

struct PositionCount
{
	char position[StringGameSerializer::MAX_SERIALIZATION_LENGTH];
	int count = 1;
};

