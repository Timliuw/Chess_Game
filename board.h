#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include "pieces.h"
#include "king.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "empty.h"
#include "mydisplay.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <sstream>

using namespace std;
void generate_piece(char c, shared_ptr<Pieces>& p, pair<int,int> pos, int color);
class Board {
    void real_place_piece(pair<int, int> pos1, pair<int, int> pos2);

    // bishop
    bool bishop_check(pair<int, int> pos1, pair<int, int> pos2);
    bool bishop_path_clear(pair<int, int> pos1, pair<int, int> pos2);
    
    // queen
    bool queen_check(pair<int, int> pos1, pair<int, int> pos2);
    

    // Knight
    bool knight_check(pair<int, int> pos1, pair<int, int> pos2);
     
    // rook
    bool rook_check(pair<int, int> pos1, pair<int, int> pos2);
    bool rook_path_clear(pair<int, int> pos1, pair<int, int> pos2);
    
    // king
    bool king_check(pair<int, int> pos1, pair<int, int> pos2);
    bool king_path_clear(pair<int, int> pos1, pair<int, int> pos2);
    bool valid_castling(pair<int, int> pos1, pair<int, int> pos2);

    // pawn
    bool pawn_check(pair<int, int> pos1, pair<int, int> pos2);
    bool pawn_path_clear(pair<int, int> pos1, pair<int, int> pos2);
    bool can_en_passant(pair<int, int> pos1, pair<int, int> pos2);

    // empty
    bool empty_check(pair<int, int> pos1, pair<int, int> pos2);
    
    
    public:
    //fiedls:
    bool turn;
    TextDisplay* td;
    GraphicsDisplay* gd;
    map<pair<int,int>,shared_ptr<Pieces>> pieces;
    
    Board(TextDisplay* td,GraphicsDisplay* gd);
    //Big 5:
    Board(const Board &other);
    Board(Board&& other);
    Board& operator=(const Board &other);
    Board& operator=(Board&& other);
    ~Board();

    //Methods 
    void board_init(TextDisplay* mytd, GraphicsDisplay* mygd);
    bool place_piece(pair<int, int> pos1, pair<int, int> pos2);
    bool isKingcheck(int color); //new paramter, check which king
    bool check_draw();
    bool ispieceattack(int color, pair<int, int> piecepos);
    int points_of_material(pair<pair<int,int>,pair<int,int>>);
    bool nomore_legalmove(int color);
    bool check_checkmate(int color);
    bool check_stalemate(int color);
    bool is_capturing(pair<pair<int,int>,pair<int,int>>);
    void empty_cell(pair<int, int> pos);
    void promotion(pair<int, int> pos1, pair<int, int> pos2);
    void notifyall(Pieces &p);
    //pieces
    bool virtual_check(pair<int, int> pos1, pair<int, int> pos2);
    vector<pair<int, int>> setof_legalmoves(pair<int, int> pos);
    bool check_legal_move(pair<int, int> pos1, pair<int, int> pos2);
    bool if_place_to_own_piece(pair<int, int> pos1, pair<int, int> pos2);
    void set_off_pawn();
};

#endif
