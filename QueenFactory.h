#pragma once

#include "PieceFactory.h"

class QueenFactory : public PieceFactory
{
public:
	Piece* create() const override;
};

