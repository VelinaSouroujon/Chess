#pragma once

#include "Piece.h"

class PieceFactory
{
public:
	virtual Piece* create() const = 0;
};
