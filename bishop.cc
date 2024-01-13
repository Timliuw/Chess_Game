#include "bishop.h"

Bishop::Bishop(std::pair<int, int> position, int col) :
    Pieces(position, col) {}

Bishop::~Bishop() {}

Bishop::Bishop(const Bishop& other) :
    Pieces(other) {}

Bishop& Bishop::operator=(const Bishop& other) {
    Pieces::operator=(other);
    return *this;
}

char Bishop::get_state() {
    if (color == 0) return 'b';
    return 'B';
}

PieceType Bishop::get_piece_type() {
    return PieceType::BISHOP;
}

int Bishop::get_point() { return 3; }
