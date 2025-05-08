#pragma once

#include "Move.h"

class PromotionMove : public Move
{
private:
	Piece* promotedPiece = nullptr;

public:
	PromotionMove(const char* notation);
	bool execute(Board& board) const override;
};

