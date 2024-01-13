#include "pieces.h"

Pieces::Pieces(std::pair<int, int> position, int col) : pos(position), color(col){}

Pieces::~Pieces() {}

Pieces::Pieces(const Pieces& other)
    : pos(other.pos),  // Copy the position
      color(other.color)  // Copy the color
{}  // Copy the reference to the board

Pieces& Pieces::operator=(const Pieces& other) {
    if (this == &other) return *this;
    pos = other.pos;    // Copy the position
    color = other.color; // Copy the color
    return *this;
}

pair<int,int> Pieces::get_pos() {
    return pos;
}

int Pieces::getcolor() { 
    return color; 
}

bool Pieces::if_empty_square() {
    return get_piece_type() == PieceType::EMPTY;
}
