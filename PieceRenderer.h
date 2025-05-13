#pragma once

class Pawn;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;

class PieceRenderer
{
public:
	virtual ~PieceRenderer() = default;

	virtual wchar_t getRepresentation(const Pawn& pawn) const = 0;
	virtual wchar_t getRepresentation(const Rook& rook) const = 0;
	virtual wchar_t getRepresentation(const Knight& knight) const = 0;
	virtual wchar_t getRepresentation(const Bishop& bishop) const = 0;
	virtual wchar_t getRepresentation(const Queen& queen) const = 0;
	virtual wchar_t getRepresentation(const King& king) const = 0;
};

