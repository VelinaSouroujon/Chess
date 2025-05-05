#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	bool isValidMove(const Move& move) const override;
};

