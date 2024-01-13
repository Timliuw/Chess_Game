#include "knight.h"
Knight::Knight(std::pair<int, int> position, int col) :
    Pieces(position, col) {}

Knight::~Knight() {}

Knight::Knight(const Knight& other) :
    Pieces(other) {}

Knight& Knight::operator=(const Knight& other) {
    Pieces::operator=(other);
    return *this;
}

char Knight::get_state() {
    if (color == 0) return 'n';
    else if (color == 1) return 'N';
}

PieceType Knight::get_piece_type() {
    return PieceType::KNIGHT;
}

int Knight::get_point() { return 3; }
