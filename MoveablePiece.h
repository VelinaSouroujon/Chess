#pragma once

#include "Piece.h"

class MoveablePiece : public Piece
{
private:
	bool isInitialization = true;
	bool hasMoved = false;

protected:
	bool getIsInitialization() const;
	void setPosition(const ChessCoordinate& value) override;

public:
	MoveablePiece(PieceColor color);

	bool getHasMoved() const;
};

