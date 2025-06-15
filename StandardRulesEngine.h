#pragma once

#include "RulesEngine.h"
#include "ChessCoordinate.h"
#include "PiecesGameInfo.h"

class StandardRulesEngine : public RulesEngine
{
private:
	static const int REPETITION_COUNT_FOR_DRAW = 3;

	bool kingHasLegalMoves(Game& game) const;
	bool canBlockCheck(Game& game, const ChessCoordinate* pathBetweenKingAndAttacker, int pathLength) const;
	CheckState getCheckState(const Game& game, int& singleCheckAttackingPieceIdx) const;
	bool canOneSideMoveToSquare(Game& game, PieceColor sideColor, const ChessCoordinate& targetSquare, const Piece* excludedPiece = nullptr) const;
	bool insufficientMaterialForSide(const OneColorPieces& side) const;
	bool isStalemate(Game& game) const;
	bool isThreefoldRepetition(Game& game) const;

protected:
	bool isWin(Game& game, CheckState& checkState) const override;
	bool isDraw(Game& game) const override;

public:
	GameResult getResult(Game& game) const override;
};

