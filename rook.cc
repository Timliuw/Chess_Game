#include "rook.h"

Rook::Rook(std::pair<int, int> position, int col) :
    Pieces(position, col), has_rook_moved{false} {}

Rook::~Rook() {}

Rook::Rook(const Rook& other) :
    Pieces(other),
    has_rook_moved(other.has_rook_moved) {}

Rook& Rook::operator=(const Rook& other) {
    Pieces::operator=(other);
    has_rook_moved = other.has_rook_moved;
    return *this;
}

char Rook::get_state() {
    if (color == 0) return 'r';
    else if (color == 1) return 'R';
}

PieceType Rook::get_piece_type() {
    return PieceType::ROOK;
}

int Rook::get_point() { return 5; }
