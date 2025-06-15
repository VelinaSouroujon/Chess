#pragma once

#include "Move.h"

class PromotionMove : public Move
{
private:
	Piece* promotedPiece = nullptr;

protected:
	Piece* getPiece(Board& board) const override;

public:
	PromotionMove(const char* notation);
	bool execute(Game& game) override;
};

