#include "Pawn.h"
#include "Move.h"
#include "CommonUtils.h"

void Pawn::setPosition(const ChessCoordinate& coordinate)
{
	const int EN_PASSANT_POSSIBLE_ROW_DIFF = 2;
	int absRowDiff = CommonUtils::abs(coordinate.getRow() - getPosition().getRow());

	MoveablePiece::setPosition(coordinate);

	if (absRowDiff == EN_PASSANT_POSSIBLE_ROW_DIFF)
	{
		mediator.notifyMove(*this);
	}
}

Pawn::Pawn(PieceColor color, PieceMediator& pawnMediator) 
	: MoveablePiece(color),
	mediator(pawnMediator)
{

}

char Pawn::getPieceNotation() const
{
	return Constants::PAWN_NOTATION;
}

bool Pawn::isSufficientForWin() const
{
	return true;
}

bool Pawn::isValidMove(const Move& move) const
{
	if (!Piece::isValidMove(move))
	{
		return false;
	}

	const ChessCoordinate& from = move.getFrom();
	const ChessCoordinate& to = move.getTo();

	int rowDiff = to.getRow() - from.getRow();

	if ((int) getColor() * rowDiff < 0)
	{
		return false;
	}

	if (move.isCaptureMove())
	{
		return rowDiff == (int)getColor()
			&& to.isSameDiagonal(from);
	}

	int maxRowDiffNonCapture = 1;
	if (!getHasMoved())
	{
		maxRowDiffNonCapture *= 2;
	}

	return CommonUtils::abs(rowDiff) <= maxRowDiffNonCapture
		&& to.isSameCol(from);
}

void Pawn::fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const
{
	const int STEPS = 1;
	int factor = (int) getColor();

	PieceDirection forwardDirection(0, factor, STEPS, CaptureState::NonCapture);
	PieceDirection captureLeftDirection(-1, factor, STEPS, CaptureState::Capture);
	PieceDirection captureRightDirection(1, factor, STEPS, CaptureState::Capture);

	directions.add(forwardDirection);
	directions.add(captureLeftDirection);
	directions.add(captureRightDirection);
}

wchar_t Pawn::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Pawn::clone() const
{
	return new Pawn(*this);
}
