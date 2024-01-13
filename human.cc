#include "human.h"

Human::Human(Board *b, int color) : Player{b, color} {}

pair<pair<int, int>, pair<int,int>> Human::generate_move() {
    pair<pair<int, int>, pair<int, int>> move;
    string start;
    string end;
    cin >> start;
    cin >> end;

    move.first.second = start[0] - 'a';
    move.first.first = start[1] - '1';
    move.second.second = end[0] - 'a';
    move.second.first = end[1] - '1';

    // check if the move is inside the board
    if (move.first.first < 0 || move.first.first > 7 || move.first.second < 0 || move.first.second > 7 || move.second.first < 0 || move.second.first > 7 || move.second.second < 0 || move.second.second > 7) {
        string error = "Invalid move";
        throw std::invalid_argument(error);
    }
    return move;
};
