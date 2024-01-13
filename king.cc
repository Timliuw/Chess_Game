#include "king.h"
using namespace std;
King::King(std::pair<int, int> position, int col) : 
    Pieces(position, col), has_king_moved(false), castling_move{false} {}

King::~King() {};

King::King(const King& other): 
    Pieces(other),  // Pieces class also has a copy constructor
    has_king_moved(other.has_king_moved),
    castling_move(other.castling_move) {}

King& King::operator=(const King& other) {
    Pieces::operator=(other);
    has_king_moved = other.has_king_moved;
    castling_move = other.castling_move;
    return *this;
}

char King::get_state() {
    if (color == 0) return 'k';
    else if (color == 1) return 'K';
}

PieceType King::get_piece_type() {
    return PieceType::KING;
}

int King::get_point() { return 0; }
