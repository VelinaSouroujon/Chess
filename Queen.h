#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	bool isValidMove(const Move& move) const override;
};

