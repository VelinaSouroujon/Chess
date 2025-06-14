#pragma once

#include "Game.h"
#include "ChessCoordinate.h"

class Move
{
private:
	char pieceNotation = Constants::PAWN_NOTATION;
	ChessCoordinate from;
	ChessCoordinate to;
	bool isCapture = false;

	void assignCoordinates(const char* notation);
	static ChessCoordinate convertToCoordinate(const char* notation, int letterNotationIdx);

	void updateIndirectKingAttackers(const ChessCoordinate& kingCoord, OneColorPieces& attackers, const Piece& movedPiece, const Board& board) const;

protected:
	virtual Piece* getPiece(Board& board) const;
	virtual bool isLegalMove(const Board& board, PieceColor turnToMove) const;

public:
	Move() = default;
	virtual ~Move() = default;
	Move(const char* notation);
	Move(const ChessCoordinate& from, const ChessCoordinate& to, bool isCapture);

	const ChessCoordinate& getFrom() const;
	const ChessCoordinate& getTo() const;
	bool isCaptureMove() const;
	bool tryConfigureEnPassant(const ChessCoordinate* gameEnPassantSquare, const Piece& pieceToMove, Piece* pieceToBeRemoved, Board& board) const;

	virtual bool execute(Game& game);
	virtual bool canExecute(Game& game);

	static const ChessCoordinate& convertToCoordinateFrom(const char* notation, char& pieceNotation);
	static const ChessCoordinate& convertToCoordinateTo(const char* notation);
};

