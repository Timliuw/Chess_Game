#include "empty.h"

Empty::Empty(std::pair<int, int> position, int col) :
    Pieces(position, col) {}

Empty::~Empty() {}

Empty::Empty(const Empty& other):
    Pieces(other) {}

Empty& Empty::operator=(const Empty& other) {
    Pieces::operator=(other);
    return *this;
}

char Empty::get_state() {
    return ' '; //no use
}

PieceType Empty::get_piece_type() {
    return PieceType::EMPTY;
}

int Empty::get_point() { return 0; }
