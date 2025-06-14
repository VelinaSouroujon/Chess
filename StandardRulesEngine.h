#pragma once

#include "RulesEngine.h"
#include "ChessCoordinate.h"
#include "OneColorPieces.h"

class StandardRulesEngine : public RulesEngine
{
private:
	bool kingHasLegalMoves(const Game& game) const;
};
