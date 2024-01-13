#ifndef MATCH_H
#define MATCH_H

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include "board.h"
#include "player.h"
#include "human.h"
#include "computer.h"

using namespace std;

class Match {
    float white_score = 0;
    float black_score = 0;
    Board* board;

    pair<int, int> process_coordinate(string coordinate);

    public:
    Match(Board *b);
    void game_init();
    void interpreter();
};
#endif
