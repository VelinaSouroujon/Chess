#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	bool isValidMove(const Move& move) const override;
};

