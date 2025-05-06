#pragma once

#include "PieceFactory.h"

class BishopFactory : public PieceFactory
{
public:
	Piece* create() const override;
};

