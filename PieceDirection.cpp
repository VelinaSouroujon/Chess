#include <stdexcept>
#include "PieceDirection.h"
#include "CommonUtils.h"

PieceDirection::PieceDirection(int x, int y, int steps, CaptureState captureState)
    : xDirection(x), yDirection(y), steps(steps), captureState(captureState)
{

}

int PieceDirection::x() const
{
    return xDirection;
}

int PieceDirection::y() const
{
    return yDirection;
}

int PieceDirection::getSteps() const
{
    return steps;
}

CaptureState PieceDirection::getCaptureState() const
{
    return captureState;
}

void PieceDirection::setX(int x)
{
    xDirection = x;
}

void PieceDirection::setY(int y)
{
    yDirection = y;
}

void PieceDirection::setSteps(int steps)
{
    const int MIN_STEPS = 1;
    const int MAX_STEPS = Constants::BOARD_SIZE - 1;

    if (!CommonUtils::isInRange(steps, MIN_STEPS, MAX_STEPS))
    {
        throw std::invalid_argument("Invalid number of steps (the number of squares a piece can go through)");
    }

    this->steps = steps;
}

void PieceDirection::setCaptureState(CaptureState captureState)
{
    this->captureState = captureState;
}
