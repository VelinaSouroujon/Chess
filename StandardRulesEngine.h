#pragma once

#include "RulesEngine.h"
#include "ChessCoordinate.h"
#include "PiecesGameInfo.h"

class StandardRulesEngine : public RulesEngine
{
private:
	bool kingHasLegalMoves(const Game& game) const;
	bool canBlockCheck(Game& game, const ChessCoordinate* pathBetweenKingAndAttacker, int pathLength) const;
	CheckState getCheckState(const Game& game, int& singleCheckAttackingPieceIdx) const;
	bool canOneSideMoveToSquare(Game& game, PieceColor sideColor, const ChessCoordinate& targetSquare, const Piece* excludedPiece = nullptr) const;
protected:
	bool isWin(Game& game, CheckState& checkState) const override;
};
