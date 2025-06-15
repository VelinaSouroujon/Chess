#pragma once

#include "Constants.h"
#include "ChessCoordinate.h"

class Piece;

class Board
{
private:
	Piece* board[Constants::BOARD_SIZE][Constants::BOARD_SIZE]{ nullptr };

	int getBoardRowIdx(const ChessCoordinate& coordinate) const;
	int getBoardColIdx(const ChessCoordinate& coordinate) const;

	bool getPathBetweenSameRow(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const;
	bool getPathBetweenSameCol(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const;
	bool getPathBetweenSameDiagonalLeftToRight(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const;
	bool getPathBetweenSameDiagonalRightToLeft(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const;
	bool getPathBetweenSameDiagonal(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const;

public:
	Board() = default;
	Board(const Board& other) = delete;
	Board& operator=(const Board& other) = delete;

	~Board();

	const Piece* at(const ChessCoordinate& coordinate) const;
	Piece* at(const ChessCoordinate& coordinate);
	void setAt(const ChessCoordinate& coordinate, Piece* piece);
	void simulateSetAt(const ChessCoordinate& coordinate, Piece* piece);

	const Piece* at(char col, int row) const;
	Piece* at(char col, int row);
	void setAt(char col, int row, Piece* piece);
	void simulateSetAt(char col, int row, Piece* piece);

	void deletePiece(Piece*& piece);

	bool tryGetPathBetweenTwoSquares(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord, ChessCoordinate* path, int& pathLength) const;
	bool isPieceBetween(const ChessCoordinate& firstCoord, const ChessCoordinate& secondCoord) const;
	int getSize() const;
};

