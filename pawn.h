#ifndef PAWN_H
#define PAWN_H

#include <iostream> 
#include <string>
#include <utility>
#include "pieces.h"
using namespace std;
class Pawn : public Pieces {   
public:
    bool has_pawn_moved; // when should I update this 
    pair<int, int> en_passant_pos;
    bool if_move_two_sqaures; // check if last move is two
    bool get_if_move_two_sqaures();
    Pawn(std::pair<int, int> position, int col);
    Pawn(const Pawn& other); // copy ctor
    ~Pawn() override;
    Pawn& operator=(const Pawn& other); // copy assignment operator
    
    char get_state() override;
    PieceType get_piece_type() override;
    int get_point() override;
};

#endif
