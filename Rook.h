#pragma once

#include "MoveablePiece.h"
#include "PieceMediator.h"
#include "ChessCoordinate.h"

class Rook : public MoveablePiece
{
private:
	PieceMediator* mediator = nullptr;

protected:
	void setPosition(const ChessCoordinate& coordinate) override;

public:
	Rook(PieceColor color, PieceMediator* mediator = nullptr);

	char getPieceNotation() const override;
	bool isSufficientForWin() const override;
	bool isValidMove(const Move& move) const override;
	void fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const override;
	wchar_t accept(const PieceRenderer& renderer) const override;

	Piece* clone() const override;
};

