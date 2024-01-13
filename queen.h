#ifndef QUEEN_H
#define QUEEN_H

#include <iostream> 
#include <string>
#include <utility>
#include "pieces.h"
using namespace std;
class Queen : public Pieces {
public:
    Queen(std::pair<int, int> position, int col);
    Queen(const Queen& other);
    ~Queen();
    Queen& operator=(const Queen& other);
    
    char get_state();
    PieceType get_piece_type() override;
    int get_point() override;
};

#endif
