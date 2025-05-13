#pragma once

#include "PieceRenderer.h"

class UnicodePieceRenderer : public PieceRenderer
{
public:
	wchar_t getRepresentation(const Pawn& pawn) const override;
	wchar_t getRepresentation(const Rook& rook) const override;
	wchar_t getRepresentation(const Knight& knight) const override;
	wchar_t getRepresentation(const Bishop& bishop) const override;
	wchar_t getRepresentation(const Queen& queen) const override;
	wchar_t getRepresentation(const King& king) const override;
};

