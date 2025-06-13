#pragma once

#include "Enums.h"

class Game;

class RulesEngine
{
protected:
	virtual bool isWin(Game& game, CheckState& checkState) const = 0;
	virtual bool isDraw(Game& game) const = 0;

public:
	virtual ~RulesEngine() = default;

	virtual GameResult getResult(Game& game) const = 0;
};

