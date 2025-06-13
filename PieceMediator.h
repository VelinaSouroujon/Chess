#pragma once

#include "Piece.h"

class PieceMediator
{
public:
	virtual ~PieceMediator() = default;

	virtual void notifyMove(const Piece& piece) = 0;
};

