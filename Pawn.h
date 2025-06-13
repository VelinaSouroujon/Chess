#pragma once

#include "Board.h"
#include "MoveablePiece.h"
#include "PieceMediator.h"

class Pawn : public MoveablePiece
{
private:
	PieceMediator& mediator;

protected:
	void setPosition(const ChessCoordinate& coordinate) override;

public:
	Pawn(PieceColor color, PieceMediator& pawnMediator);

	char getPieceNotation() const override;
	bool isValidMove(const Move& move) const override;
	wchar_t accept(const PieceRenderer& renderer) const override;

	Piece* clone() const override;
};

