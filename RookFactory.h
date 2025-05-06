#pragma once

#include "PieceFactory.h"

class RookFactory : public PieceFactory
{
public:
	Piece* create() const override;
};

