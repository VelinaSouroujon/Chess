#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	bool isValidMove(const Move& move) const override;
};

