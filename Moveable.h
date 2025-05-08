#pragma once

class Moveable
{
private:
	bool hasMoved = false;

protected:
	void setHasMoved(bool value);

public:
	bool getHasMoved() const;
};

