#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human : public Player{
    public:
    pair<pair<int, int>, pair<int, int>> generate_move() override;
    Human(Board *b, int color);
};

#endif
