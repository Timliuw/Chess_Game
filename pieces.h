#ifndef PIECES_H
#define PIECES_H

#include <iostream> 
#include <string>
#include <utility>
#include <vector>
#include <memory>

using namespace std;

enum class PieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY
};

class Board;

class Pieces {
public:
    pair<int, int> pos;
    int color; // 0 is black 1 is white 2 is empty
    Pieces(std::pair<int, int> position, int col);
    Pieces(const Pieces& other);
    Pieces& operator=(const Pieces& other);
    virtual ~Pieces();
    virtual char get_state() = 0;

    virtual PieceType get_piece_type() = 0;
    int getcolor();
    pair<int,int> get_pos();
    virtual int get_point() = 0;
    bool if_empty_square();
};

#endif
