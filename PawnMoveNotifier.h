#pragma once

#include "GameNotifier.h"
#include "PieceMediator.h"

class PawnMoveNotifier : public GameNotifier, public PieceMediator
{
public:
	void notifyGame(const Piece& sender) override;
	void notifyMove(const Piece& piece) override;
};

