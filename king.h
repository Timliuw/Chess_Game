#ifndef KING_H
#define KING_H
#include <iostream> 
#include <string>
#include <utility>
#include "pieces.h"
using namespace std;
class King : public Pieces {
public:
    bool has_king_moved;
    bool castling_move;
    King(std::pair<int, int> position, int col);
    ~King() override;
    King(const King& other); // copy ctor
    King& operator=(const King& other); // copy assignment operator
   
    char get_state() override;
    PieceType get_piece_type() override;
    int get_point() override;
};

#endif
