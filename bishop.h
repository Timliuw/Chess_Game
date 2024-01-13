#ifndef BISHOP_H
#define BISHOP_H

#include <iostream> 
#include <string>
#include <utility>
#include <memory>
#include "pieces.h"
#include "board.h"

using namespace std;
class Bishop : public Pieces {
public:
    Bishop(std::pair<int, int> position, int col);
    ~Bishop() override;
    Bishop(const Bishop& other); // copy ctor
    Bishop& operator=(const Bishop& other); // copy assignment operator
    
    char get_state() override;
    PieceType get_piece_type() override;
    int get_point() override;
};
#endif
