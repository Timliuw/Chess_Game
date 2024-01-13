#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include "board.h"

using namespace std;

class Board;

// pure virtual class for human and computer
class Player {
    public:
    Board* board;
    int color;
    Player(Board* board, int color);
    virtual pair<pair<int, int>, pair<int,int>> generate_move() = 0;
};
#endif
