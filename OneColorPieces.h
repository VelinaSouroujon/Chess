#pragma once

#include "Piece.h"
#include "Board.h"
#include "Constants.h"
#include "Enums.h"

class OneColorPieces
{
private:
	const Piece* pieces[Constants::PIECES_COUNT_PER_SIDE]{ nullptr };
	int size = 0;
	const PieceColor color;

public:
	OneColorPieces(PieceColor color);
	OneColorPieces(PieceColor color, const Board& board, const Piece*& king);

	int getSize() const;
	PieceColor getColor() const;
	const Piece* const* getPieces() const;
	int findIdx(const Piece& piece) const;

	bool add(const Piece& pieceToAdd);
	bool remove(const Piece& pieceToRemove);
	void removeAt(int idx);
	bool replace(const Piece& oldPiece, const Piece& newPiece);
	void clear();

	bool isSquareAttacked(const ChessCoordinate& targetSquare, const Board& board, const Piece* excludedPiece = nullptr) const;

	const Piece& operator[](int index) const;
};

