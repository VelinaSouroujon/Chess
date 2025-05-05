#pragma once

#include "Game.h"
#include "ChessCoordinate.h"

class Move
{
private:
	Piece* piece = nullptr;
	ChessCoordinate from;
	ChessCoordinate to;
	bool isCapture = false;

	void free();

public:
	Move(const Game& game, const char* notation);
	~Move();

	ChessCoordinate getFrom() const;
	ChessCoordinate getTo() const;
	bool isCaptureMove() const;
};

