#include "queen.h"
Queen::Queen(std::pair<int, int> position, int col) :
    Pieces(position, col) {}

Queen::~Queen() {}

Queen::Queen(const Queen& other) :
    Pieces(other) {}

Queen& Queen::operator=(const Queen& other) {
    Pieces::operator=(other);
    return *this;
}

char Queen::get_state() {
    if (color == 0) return 'q';
    else if (color == 1) return 'Q';
}

PieceType Queen::get_piece_type() {
    return PieceType::QUEEN;
}

int Queen::get_point() { return 9; }
