#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream> 
#include <string>
#include <utility>
#include "pieces.h"
using namespace std;
class Knight : public Pieces {
public:
    Knight(std::pair<int, int> position, int col);
    ~Knight() override;
    Knight(const Knight& other); // copy ctor
    Knight& operator=(const Knight& other); // copy assignment operator
    
    char get_state() override;
    PieceType get_piece_type() override;
    int get_point() override;
};

#endif
