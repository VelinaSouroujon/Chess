#pragma once

#include "GameNotifier.h"
#include "PieceMediator.h"

class EnPassantNotifier : public GameNotifier, public PieceMediator
{
private:
	ChessCoordinate enPassantSquare;

public:
	void notifyGame(const Piece& sender) override;
	void notifyMove(const Piece& piece) override;
};

