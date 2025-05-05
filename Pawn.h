#pragma once

#include "Piece.h"

class Pawn : public Piece
{
public:
	bool isValidMove(const Move& move) const override;
};

