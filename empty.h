#ifndef EMPTY_H
#define EMPTY_H

#include <iostream> 
#include <string>
#include <utility>
#include "pieces.h"
using namespace std;
class Empty : public Pieces {
public:
    Empty(std::pair<int, int> position, int col);
    Empty(const Empty& other);
    ~Empty();
    Empty& operator=(const Empty& other);

    char get_state();
    PieceType get_piece_type() override;
    int get_point() override;
};

#endif
