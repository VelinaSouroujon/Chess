#pragma once

#include "Constants.h"
#include "Enums.h"

class PieceDirection
{
private:
	int xDirection = 0;
	int yDirection = 0;
	int steps = 0;
	CaptureState captureState = CaptureState::DoesNotMatter;

public:
	PieceDirection() = default;
	PieceDirection(int x, int y, int steps = Constants::BOARD_SIZE - 1, CaptureState captureState = CaptureState::DoesNotMatter);

	int x() const;
	int y() const;
	int getSteps() const;
	CaptureState getCaptureState() const;

	void setX(int x);
	void setY(int y);
	void setSteps(int steps);
	void setCaptureState(CaptureState captureState);
};

