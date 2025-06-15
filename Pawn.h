#pragma once

#include "Board.h"
#include "MoveablePiece.h"
#include "PieceMediator.h"

class Pawn : public MoveablePiece
{
private:
	PieceMediator& enPassantNotifier;
	PieceMediator& pawnMoveNotifier;

protected:
	void setPosition(const ChessCoordinate& coordinate) override;

public:
	Pawn(PieceColor color, PieceMediator& enPassantNotifier, PieceMediator& pawnMoveNotifier);

	char getPieceNotation() const override;
	bool isSufficientForWin() const override;
	bool isValidMove(const Move& move) const override;
	void fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const override;
	wchar_t accept(const PieceRenderer& renderer) const override;

	Piece* clone() const override;
};

