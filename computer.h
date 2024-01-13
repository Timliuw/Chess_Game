#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player {
    public:
    int level;
    Computer(Board* b, int color, int level);
    pair<pair<int, int>, pair<int, int>> generate_move() override;
};

#endif
