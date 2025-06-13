#pragma once

#include "Piece.h"

class MoveablePiece : public Piece
{
private:
	bool isSetDuringInit = true;
	bool hasMoved = false;

protected:
	void setPosition(const ChessCoordinate& value) override;

public:
	MoveablePiece(PieceColor color);

	bool getHasMoved() const;
};

