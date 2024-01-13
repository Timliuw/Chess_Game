#include "pawn.h"

Pawn::Pawn(std::pair<int, int> position, int col) :
    Pieces(position, col), has_pawn_moved(false), if_move_two_sqaures{false},
    en_passant_pos{make_pair(-1, -1)} {}

Pawn::~Pawn() {};

Pawn::Pawn(const Pawn& other) :
    Pieces(other),  // Pieces class also has a copy constructor
    has_pawn_moved(other.has_pawn_moved),
    if_move_two_sqaures{other.if_move_two_sqaures},
    en_passant_pos{other.en_passant_pos} {}


Pawn& Pawn::operator=(const Pawn& other) {
    Pieces::operator=(other);
    has_pawn_moved = other.has_pawn_moved;
    if_move_two_sqaures = other.if_move_two_sqaures;
    en_passant_pos = other.en_passant_pos;
    return *this;
}

bool Pawn::get_if_move_two_sqaures() { return if_move_two_sqaures; }



char Pawn::get_state() {
    if (color == 0) return 'p';
    else if (color == 1) return 'P';
    else return '?';//debug
}

PieceType Pawn::get_piece_type()  {
    return PieceType::PAWN;
}

int Pawn::get_point() { return 1; }
