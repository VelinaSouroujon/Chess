#pragma once

#include "Piece.h"
#include "Constants.h"
#include "ChessCoordinate.h"

class Board
{
private:
	Piece* board[Constants::BOARD_SIZE][Constants::BOARD_SIZE]{ nullptr };

	int getBoardRowIdx(const ChessCoordinate& coordinate) const;
	int getBoardColIdx(const ChessCoordinate& coordinate) const;

	bool isPieceBetweenSameRow(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const;
	bool isPieceBetweenSameCol(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const;
	bool isPieceBetweenSameDiagonalLeftToRight(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const;
	bool isPieceBetweenSameDiagonalRightToLeft(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const;
	bool isPieceBetweenSameDiagonal(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const;

public:
	const Piece* at(const ChessCoordinate& coordinate) const;
	Piece* at(const ChessCoordinate& coordinate);
	void setAt(const ChessCoordinate& coordinate, Piece* piece);
	void simulateSetAt(const ChessCoordinate& coordinate, Piece* piece);

	const Piece* at(char col, int row) const;
	Piece* at(char col, int row);
	void setAt(char col, int row, Piece* piece);
	void simulateSetAt(char col, int row, Piece* piece);

	//void createPieceOnSquare(char pieceNotation, const ChessCoordinate& square, PieceColor color);
	void deletePiece(Piece*& piece);

	bool isPieceBetween(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const;
	bool removeAt(const ChessCoordinate& coordinate);
	int getSize() const;
};

