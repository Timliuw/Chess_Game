#ifndef ROOK_H
#define ROOK_H

#include <iostream> 
#include <string>
#include <utility>
#include "pieces.h"
using namespace std;
class Rook : public Pieces {
public:
    bool has_rook_moved;
    Rook(std::pair<int, int> position, int col);
    ~Rook() override;
    Rook(const Rook& other); // copy ctor
    Rook& operator=(const Rook& other); // copy assignment operator
    
    char get_state() override;
    PieceType get_piece_type() override;
    int get_point() override;
};

#endif
