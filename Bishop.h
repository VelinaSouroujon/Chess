#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	bool isValidMove(const Move& move) const override;
};

