#pragma once

#include "Game.h"
#include "ChessCoordinate.h"
#include "PieceFactory.h"

class Move
{
private:
	static PieceFactory* pieceCharMap[Constants::ENGLISH_LETTERS_COUNT];

	Piece* piece = nullptr;
	ChessCoordinate from;
	ChessCoordinate to;
	bool isCapture = false;

	void initPieceCharMap();
	void freePieceCharMap();
	void free();

public:
	Move(const Game& game, const char* notation);
	~Move();

	ChessCoordinate getFrom() const;
	ChessCoordinate getTo() const;
	bool isCaptureMove() const;

	Piece* getPromotingPiece(char pieceChar) const;
};

