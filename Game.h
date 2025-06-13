#pragma once

#include "ChessVariant.h"
#include "PiecesGameInfo.h"
#include "RulesEngine.h"

class BinaryGameSerializer;

class Game
{
private:
	ChessVariant& chessVariant;
	RulesEngine& rulesEngine;

	PiecesGameInfo white;
	PiecesGameInfo black;

	PieceColor turnToMove = PieceColor::White;

	ChessCoordinate enPassantSquare;
	EnPassantState enPassantState = EnPassantState::None;

public:
	friend class BinaryGameSerializer;

	Game(ChessVariant& chessVariant, RulesEngine& rulesEngine);

	const PiecesGameInfo& playingSide() const;
	const PiecesGameInfo& awaitingSide() const;
	const PiecesGameInfo& sameColorPiecesInfo(PieceColor color) const;
	const PiecesGameInfo& oppositeColorPiecesInfo(PieceColor color) const;

	PieceColor getTurnToMove() const;
	PieceColor getAwaitingSideColor() const;
	const ChessVariant& getChessVariant() const;
	const ChessCoordinate* getEnPassantSquare() const;
	const RulesEngine& rules() const;

	PiecesGameInfo& playingSide();
	PiecesGameInfo& awaitingSide();
	PiecesGameInfo& sameColorPiecesInfo(PieceColor color);
	PiecesGameInfo& oppositeColorPiecesInfo(PieceColor color);
	ChessVariant& getChessVariant();
	void changeTurn();
	void setEnPassantSquare(const ChessCoordinate& enPassantSquare);
};

