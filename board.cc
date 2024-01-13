#include "board.h"
#include <memory>
using namespace std;

//general ctor
Board::Board(TextDisplay* td,GraphicsDisplay* gd):turn{true}, td{td}, gd{gd} {
    // fill pieces with empty pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8 ; ++j) {
            pair<int,int> pos = make_pair(i,j);
            int color;
            // black pieces on row 0 and 1
            // white pieces on row 6 and 7
            if (i < 2) {
                color = 0;
            } else if (i > 5) {
                color = 1;
            } else {
                color = 2;
            }
            pieces[pos] = make_shared<Empty>(pos, color);
        }
    }
}

//copy ctor
Board::Board(const Board &other) {
    turn = other.turn;
    td = nullptr; //copied board no need td
    gd = nullptr; //no need gd
    for (auto[key , value] : other.pieces) {
        if (value->get_piece_type() == PieceType::KING) {
            auto p = dynamic_pointer_cast<King>(value);
            pieces[key] = make_shared<King> (*p);
        } else if (value->get_piece_type() == PieceType::QUEEN) {
            auto p = dynamic_pointer_cast<Queen>(value);
            pieces[key] = make_shared<Queen> (*p);
        } else if (value->get_piece_type() == PieceType::ROOK) {
            auto p = dynamic_pointer_cast<Rook>(value);
            pieces[key] = make_shared<Rook> (*p);
        } else if (value->get_piece_type() == PieceType::BISHOP) {
            auto p = dynamic_pointer_cast<Bishop>(value);
            pieces[key] = make_shared<Bishop> (*p);
        } else if (value->get_piece_type() == PieceType::KNIGHT) {
            auto p = dynamic_pointer_cast<Knight>(value);
            pieces[key] = make_shared<Knight> (*p);
        } else if (value->get_piece_type() == PieceType::PAWN) {
            auto p = dynamic_pointer_cast<Pawn>(value);
            pieces[key] = make_shared<Pawn> (*p);
        } else if (value->get_piece_type() == PieceType::EMPTY) {
            auto p = dynamic_pointer_cast<Empty>(value);
            pieces[key] = make_shared<Empty> (*p);
        }      
    }
}

//copy assignment operator
Board& Board::operator=(const Board &other) {
    if (this != &other) { // Check for self-assignment
        turn = other.turn;
        td = nullptr; 
        gd = nullptr; 
        for (auto[key , value] : other.pieces) {
            if (value->get_piece_type() == PieceType::KING) {
                auto p = dynamic_pointer_cast<King>(value);
                pieces[key] = make_shared<King> (*p);
            } else if (value->get_piece_type() == PieceType::QUEEN) {
                auto p = dynamic_pointer_cast<Queen>(value);
                pieces[key] = make_shared<Queen> (*p);
            } else if (value->get_piece_type() == PieceType::ROOK) {
                auto p = dynamic_pointer_cast<Rook>(value);
                pieces[key] = make_shared<Rook> (*p);
            } else if (value->get_piece_type() == PieceType::BISHOP) {
                auto p = dynamic_pointer_cast<Bishop>(value);
                pieces[key] = make_shared<Bishop> (*p);
            } else if (value->get_piece_type() == PieceType::KNIGHT) {
                auto p = dynamic_pointer_cast<Knight>(value);
                pieces[key] = make_shared<Knight> (*p);
            } else if (value->get_piece_type() == PieceType::PAWN) {
                auto p = dynamic_pointer_cast<Pawn>(value);
                pieces[key] = make_shared<Pawn> (*p);
            } else if (value->get_piece_type() == PieceType::EMPTY) {
                auto p = dynamic_pointer_cast<Empty>(value);
                pieces[key] = make_shared<Empty> (*p);
            }      
        }
    }
    return *this;
}

//move assignment operator
Board& Board::operator=(Board&& other) {
    turn = other.turn;
    td = nullptr; 
    gd = nullptr; 
    swap(pieces, other.pieces);
    return *this;
}

//dtor
Board::~Board(){} //does nothing

//generate pieces according to char
void generate_piece(char c, shared_ptr<Pieces>& p, pair<int,int> pos, int color) {
    if (c == 'R' || c == 'r') {
        p = make_shared<Rook>(pos, color);
    } else if (c == 'N' || c == 'n') {
        p = make_shared<Knight>(pos, color);
    } else if (c == 'B' || c == 'b') {
        p = make_shared<Bishop>(pos, color);
    } else if (c == 'Q' || c == 'q') {
        p = make_shared<Queen>(pos, color);
    } else if (c == 'K' || c == 'k') {
        p = make_shared<King>(pos, color);
    } else if (c == 'P' || c == 'p') {
        p = make_shared<Pawn>(pos, color);
    } else {
        p = make_shared<Empty>(pos, color);
    }
}


void Board::board_init(TextDisplay* mytd, GraphicsDisplay* mygd) {
  turn = true;
  //initialize graphicsdisplay
  td = mytd;
  gd = mygd;

  char c = ' ';
  std::stringstream ss;
  ss << c;
  std::string s = ss.str();

  //display initialization
  for (int i = 0; i < 8; ++i) {
    gd->xw.drawString(20, 425 - i * 50, to_string(i+1));
    if (i == 0 || i == 7) {
        //piece part
        string piece_string = "RNBQKBNR";
        for (int k = 0; k < 8; ++k) {
            pair<int, int> pos = make_pair(i, k);
            string cur_string = piece_string.substr(k,1);
            char cur_c = cur_string[0];
            piece_string.substr(1);
            if (i == 7) cur_c += 'a' - 'A';

            ostringstream oss{};
            oss << cur_c;
            string s;
            s = oss.str(); //s we actually use
            td->cells[pos] = cur_c;

            int x = 40 + k * 50;
            int y = 400 - i * 50;

            int color = 0; //black
            int rec_color = 4;
            if (cur_c <= 'a')  color = 1; //white
            if (color == 0) rec_color = 2; 
            gd->xw.fillRectangle(x, y, 50, 50, rec_color);
            gd->xw.drawString(x+25, y+25, s);
            generate_piece(cur_c, pieces[pos], pos, color);
        }
    } else {       
        for (int j = 0; j < 8; ++j) {
            char cur_c;
            pair<int, int> pos = make_pair(i, j);
            //pawn
            if (i == 1) cur_c = 'P';
            if (i == 6) cur_c = 'p';
            //non-piece part
            if (i < 6 && i > 1) {
                if ((i + j) % 2 == 0) cur_c = '_';
                else cur_c = ' ';
            }
            td->cells[pos] = cur_c;

            ostringstream oss{};
            oss << cur_c;
            string s;
            s = oss.str(); //s we actually use
            td->cells[pos] = cur_c;
            int color; 
            if (cur_c == 'p') {
                color = 0;//black
            } else if (cur_c == 'P'){
                color = 1;//white
            } else color = 2;

            int x = 40 + j * 50;
            int y = 400 - i * 50;
            int rec_color;
            if (color == 0) rec_color = 2; 
            else if (color == 1) rec_color = 4;
            else if ((i + j) % 2 == 0) rec_color = 1;
            else rec_color = 0;
            gd->xw.fillRectangle(x, y, 50, 50, rec_color);
            if (cur_c != ' ' && cur_c != '_') {
                gd->xw.drawString(x+25, y+25, s);
            }
            


            generate_piece(cur_c, pieces[pos], pos, color);
        }
    }
    for (int i = 0; i < 8; ++i) {
        char c = 'a' + i;
        std::ostringstream ss;
        ss << c;
        std::string s = ss.str();
        gd->xw.drawString(65 + i * 50, 470, s);
    }
  }
}

void Board::promotion(pair<int, int> pos1, pair<int, int> pos2) {
    while (1) {
        char c;
        cin >> c;
        int color = pieces[pos1]->getcolor();
        if (c == 'Q' || c == 'q') {
            pieces[pos1] = make_shared<Queen>(pos1, color);
            return;
        } else if (c == 'R' || c == 'r') {
            pieces[pos1] = make_shared<Rook>(pos1, color);
            return;
        } else if (c == 'B' || c == 'b') {
            pieces[pos1] = make_shared<Bishop>(pos1, color);
            return;
        } else if (c == 'N' || c == 'n') {
            pieces[pos1] = make_shared<Knight>(pos1, color);
            return;
        } else {
            cout << "Invalid promotion";
        }
    }
}
void Board::real_place_piece(pair<int, int> pos1, pair<int, int> pos2) {
    if (pieces[pos1]->get_piece_type() == PieceType::PAWN) {
        //promotion case
        if (pieces[pos1]->getcolor() == 0) {
            //black promotion
            if (pos2.first == 0) {
                promotion(pos1, pos2);
            }
        } else {
            //white promotion
            if (pos2.first == 7) {
                promotion(pos1, pos2);
            }
        }

        auto pp = dynamic_pointer_cast<Pawn>(pieces[pos1]);
        //en_passant case
        if (can_en_passant(pos1, pos2)) {
            auto eat_pos = pp->en_passant_pos;
            empty_cell(eat_pos);
            if (td) {
                notifyall(*pieces[eat_pos]);
            }
        }
    }


    //castling_move case
    if (pieces[pos1]->get_piece_type() == PieceType::KING) {
        auto kp = dynamic_pointer_cast<King>(pieces[pos1]);
        if (valid_castling(pos1, pos2)) {
            // char castle = pieces[pos2]->get_state();
            int old_col = pos1.second;
            int new_col = pos2.second;
            auto rookpos = make_pair(0,0);
            auto emptypos = make_pair(0,0);
            if(old_col < new_col) {
                //king moves left side
                if (kp->getcolor() == 1) {
                    rookpos = make_pair(0,5);
                    emptypos = make_pair(0,7);
                } else {
                    rookpos = make_pair(7,5);
                    emptypos = make_pair(7,7);
                }
            } else {
                if (kp->getcolor() == 1) {
                    rookpos = make_pair(0,3);
                    emptypos = make_pair(0,0);
                } else {
                    rookpos = make_pair(7,3);
                    emptypos = make_pair(7,0);
                }
            }
            empty_cell(emptypos);
            
            pieces[rookpos] = make_shared<Rook>(rookpos, pieces[pos1]->getcolor());
            if (td) {
                notifyall(*pieces[emptypos]);
                notifyall(*pieces[rookpos]);
            }
        }
    }

    if (pieces[pos1]->get_piece_type() == PieceType::PAWN) {
        auto pp = dynamic_pointer_cast<Pawn>(pieces[pos1]);
    }

    //copy piece to new pos
    if (pieces[pos1]->get_piece_type() == PieceType::KING) {
        auto p = dynamic_pointer_cast<King>(pieces[pos1]);
        pieces[pos2] = make_shared<King> (*p);
    } else if (pieces[pos1]->get_piece_type() == PieceType::QUEEN) {
        auto p = dynamic_pointer_cast<Queen>(pieces[pos1]);
        pieces[pos2] = make_shared<Queen> (*p);
    } else if (pieces[pos1]->get_piece_type() == PieceType::ROOK) {
        auto p = dynamic_pointer_cast<Rook>(pieces[pos1]);
        pieces[pos2] = make_shared<Rook> (*p);
    } else if (pieces[pos1]->get_piece_type() == PieceType::BISHOP) {
        auto p = dynamic_pointer_cast<Bishop>(pieces[pos1]);
        pieces[pos2] = make_shared<Bishop> (*p);
    } else if (pieces[pos1]->get_piece_type() == PieceType::KNIGHT) {
        auto p = dynamic_pointer_cast<Knight>(pieces[pos1]);
        pieces[pos2] = make_shared<Knight> (*p);
    } else if (pieces[pos1]->get_piece_type() == PieceType::PAWN) {
        auto p = dynamic_pointer_cast<Pawn>(pieces[pos1]);
        pieces[pos2] = make_shared<Pawn> (*p);
    } else if (pieces[pos1]->get_piece_type() == PieceType::EMPTY) {
        auto p = dynamic_pointer_cast<Empty>(pieces[pos1]);
        pieces[pos2] = make_shared<Empty> (*p);
    }
    pieces[pos2]->pos = pos2;
    empty_cell(pos1);  
    if (td) {
        notifyall(*pieces[pos1]);
        notifyall(*pieces[pos2]);
    }
}

bool Board::place_piece(pair<int, int> pos1, pair<int, int> pos2) {
    bool success = check_legal_move(pos1, pos2);
    if (success) {
        //place_piece and notify
        real_place_piece(pos1, pos2);
    }
    return success;
}

bool Board::isKingcheck(int color) {
    pair<int,int> king_pos;
    //get king pos
    for (auto[key , value] : pieces) {
        if (value->get_piece_type() == PieceType::KING &&
            value->color == color) {
            king_pos = value->get_pos();
            break;
        }
    }

    //check all opponent pieces
    for (auto[key , value] : pieces) {
        if (pieces[key]->getcolor() == color) {
            continue;
        } else if (pieces[key]->get_piece_type() == PieceType::EMPTY) {
            continue;
        } else {
            if (check_legal_move(key, king_pos)) {
                return true;
            }
        }
    }
    
    return false;
}

bool Board::ispieceattack(int color, pair<int, int> piecepos) {
    //check all opponent pieces
    for (auto[key , value] : pieces) {
        if (pieces[key]->getcolor() == color) {
            continue;
        } else if (pieces[key]->get_piece_type() == PieceType::EMPTY) {
            continue;
        } else {
            if (check_legal_move(key, piecepos)) {
                return true;
            }
        }
    }
    return false;
}


bool Board::check_draw() {
    // check if enough material on the board
    int num_pieces = 0;
    for (auto[key , value] : pieces) {
        if (pieces[key]->get_piece_type() != PieceType::EMPTY) {
            num_pieces++;
        }
    }
    if (num_pieces == 2) return true;
    if (num_pieces == 3) {
        for (auto[key , value] : pieces) {
            if (pieces[key]->get_piece_type() == PieceType::KNIGHT ||
                pieces[key]->get_piece_type() == PieceType::BISHOP) {
                return true;
            }
        }
    }
    return false;
}

bool Board::nomore_legalmove(int color) {
    for (auto[key , value] : pieces) {
        if (pieces[key]->get_piece_type() != PieceType::EMPTY &&
            value->getcolor() == color) {
            vector<pair<int,int>> valid_moves = setof_legalmoves(value->get_pos());
            if (!valid_moves.empty()) return false;  
        }
    }
    //all friend pieces have no legal move
    return true;
}

bool Board::check_checkmate(int color) {
    if (isKingcheck(color) && nomore_legalmove(color)) return true;
    return false;
}

bool Board::check_stalemate(int color){
    //inefficient, should call any_legalmove in control flow
    if (!isKingcheck(color) && nomore_legalmove(color)) return true;
    return false;
}

void Board::empty_cell(pair<int, int> pos) {
    pieces[pos] = make_shared<Empty>(pos, 2);
}

bool Board::is_capturing(pair<pair<int,int>,pair<int,int>> move) {
    pair<int,int> pos2 = move.second;
    if (pieces[pos2]->get_piece_type() != PieceType::EMPTY) {
        return true;
    }
    return false;
}

int Board::points_of_material(pair<pair<int,int>,pair<int,int>> move) {
    // calculate the difference between points in material before and after the move
    pair<int,int> pos1 = move.first;
    pair<int,int> pos2 = move.second;
    int color = pieces[pos1]->getcolor();
    int points = 0;
    if (pieces[pos2]->get_piece_type() != PieceType::EMPTY) {
        if (pieces[pos2]->getcolor() != color) {
            points += pieces[pos2]->get_point();
        } else {
            points -= pieces[pos2]->get_point();
        }
    }
    return points;
}

bool Board::bishop_check(pair<int, int> pos1, pair<int, int> pos2) {
    if (if_place_to_own_piece(pos1, pos2)) return false;
    int row_diff = abs(pos1.first - pos2.first);
    int col_diff = abs(pos1.second - pos2.second);

    if (row_diff != col_diff) return false;
    if (!bishop_path_clear(pos1, pos2)) return false;
    return true;
}

// queen checks
bool Board::queen_check(pair<int, int> pos1, pair<int, int> pos2) {
    if (if_place_to_own_piece(pos1, pos2)) return false; 

    int row_diff = abs(pos1.first - pos2.first);
    int col_diff = abs(pos1.second - pos2.second);

    // if there are pieces in the way
    if (row_diff == col_diff) {
        if (!bishop_path_clear(pos1, pos2)) return false;
    } else if ((row_diff != 0) && (col_diff != 0)) {
        return false;
    } else {
        if (!rook_path_clear(pos1, pos2)) return false;
    }

    // Check for diagonal move
    if (row_diff == col_diff) return true;

    // Check for straight move
    if (row_diff == 0 || col_diff == 0) return true;

    return false;
}

bool Board::rook_path_clear(pair<int, int> pos1, pair<int, int> pos2) {
    int row_diff = pos2.first - pos1.first;
    int col_diff = pos2.second - pos1.second;
    int row_step = (row_diff != 0) ? (row_diff / abs(row_diff)) : 0; // 1, -1 or 0
    int col_step = (col_diff != 0) ? (col_diff / abs(col_diff)) : 0; // 1, -1 or 0

    int currentRow = pos1.first + row_step;
    int currentCol = pos1.second + col_step;

    while (currentRow != pos2.first || currentCol != pos2.second) {
        if (pieces[make_pair(currentRow, currentCol)]->get_piece_type() != PieceType::EMPTY) {
            return false; 
        }
        currentRow += row_step;
        currentCol += col_step;
    }
    if (pieces[pos1]->get_piece_type() == PieceType::ROOK) {
        auto rp = dynamic_pointer_cast<Rook>(pieces[pos1]);
        rp->has_rook_moved = true; //move to legal check
        return true;
    } else {
        auto rp = dynamic_pointer_cast<Queen>(pieces[pos1]);
        return true;
    }
    
}

// pawn check
bool Board::can_en_passant(pair<int, int> pos1, pair<int, int> pos2) {
    // diagonal move of one square
    if (abs(pos1.first - pos2.first) != 1 || abs(pos1.second - pos2.second) != 1) return false;
    
    // Position of the pawn that might be captured en passant
    pair<int, int> targetPawnPos = make_pair(pos1.first, pos2.second);
    shared_ptr<Pieces> piece = pieces[targetPawnPos];
    if (piece->get_piece_type() != PieceType::PAWN) return false;

    shared_ptr<Pawn> targetPawn = dynamic_pointer_cast<Pawn>(piece);
    if (targetPawn->getcolor() == pieces[pos1]->getcolor() ) return false;
    if (!targetPawn->get_if_move_two_sqaures()) return false;
    
    dynamic_pointer_cast<Pawn>(pieces[pos1])->en_passant_pos = targetPawnPos;
    return true;
}


void Board::set_off_pawn() {
    for (auto[key , value] : pieces) {
        if (value->get_piece_type() == PieceType::PAWN && value->getcolor() != turn) {
            auto p = dynamic_pointer_cast<Pawn>(value);
            p->if_move_two_sqaures = true;
        }
    }
}

bool Board::pawn_check(pair<int, int> pos1, pair<int, int> pos2) {
    if (if_place_to_own_piece(pos1, pos2)) return false;

    int color = pieces[pos1]->getcolor();
    int row_diff = pos2.first - pos1.first;  // Forward is positive for white, negative for black
    int col_diff = pos2.second - pos1.second;

    auto targetPawn = dynamic_pointer_cast<Pawn>(pieces[pos1]);
    pieces[pos1] = targetPawn;

    // Handle forward moves
    if (col_diff == 0) {
        if (!pieces[pos2]->if_empty_square()) return false;
        // White pawn
        if (color == 1) {
            if (row_diff == 1) {
                targetPawn->if_move_two_sqaures = false;
                targetPawn->has_pawn_moved = true;
                return true;
            }

            if (row_diff == 2) {
                if (targetPawn->has_pawn_moved) return false;
                if (pawn_path_clear(pos1, pos2)) {
                    targetPawn->if_move_two_sqaures = true;
                    targetPawn->has_pawn_moved = true;
                    return true;
                }
            }
        }
        // Black pawn
        else if (color == 0) {
            if (row_diff == -1) {
                targetPawn->if_move_two_sqaures = false;
                targetPawn->has_pawn_moved = true;
                return true;
            }

            if (row_diff == -2) {
                if (targetPawn->has_pawn_moved) return false;
                if (pawn_path_clear(pos1, pos2)) {
                    targetPawn->if_move_two_sqaures = true;
                    targetPawn->has_pawn_moved = true;
                    return true;
                }
            }
        }
    }
    // Handle captures (including en passant)
    else if (abs(col_diff) == 1) {
        if ((color == 1 && row_diff == 1) || (color == 0 && row_diff == -1)) {
            if (pieces[pos2]->get_piece_type() != PieceType::EMPTY) {
                targetPawn->has_pawn_moved = true;
                targetPawn->if_move_two_sqaures = false;
                return true;
            }
            if (can_en_passant(pos1, pos2)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::pawn_path_clear(pair<int, int> pos1, pair<int, int> pos2) {
    // Check for horizontal movement
    if (pos1.second != pos2.second) return false;
    int diff = (pos1.first > pos2.first) ? -1 : 1;
   // PieceType p = pieces[make_pair(pos1.first, pos1.second + diff)]->get_piece_type(); 
    if (pieces[make_pair(pos1.first + diff, pos1.second)]->get_piece_type() != PieceType::EMPTY) {
        return false;  // Path is not clear
    }
    return true;  
}


// Knight check
bool Board::knight_check(pair<int, int> pos1, pair<int, int> pos2) {
    if (if_place_to_own_piece(pos1, pos2)) return false; 

    int row_diff = abs(pos1.first - pos2.first);
    int col_diff = abs(pos1.second - pos2.second);

    // Check for L-shaped move
    return (row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2);
}

// empty check
bool Board::empty_check(pair<int, int> pos1, pair<int, int> pos2) {
    return false;
}

// bishop checks
bool Board::bishop_path_clear(pair<int, int> pos1, pair<int, int> pos2) {
    int row_diff = pos2.first - pos1.first;
    int col_diff = pos2.second - pos1.second;
    int row_step = (row_diff > 0) ? 1 : -1;  //  direction of row increment
    int col_step = (col_diff > 0) ? 1 : -1;  //  direction of column increment

    int currentRow = pos1.first + row_step;
    int currentCol = pos1.second + col_step;

    while (currentRow != pos2.first && currentCol != pos2.second) {
        if (pieces[make_pair(currentRow, currentCol)]->get_piece_type() != PieceType::EMPTY) {
            return false; 
        }
        currentRow += row_step;
        currentCol += col_step;
    }

    return true;
}

// rook checks
bool Board::rook_check(pair<int, int> pos1, pair<int, int> pos2) {
    if (if_place_to_own_piece(pos1, pos2)) return false;
    int row_diff = abs(pos1.first - pos2.first);
    int col_diff = abs(pos1.second - pos2.second);

    if ((row_diff != 0) && (col_diff != 0)) return false;

    return rook_path_clear(pos1, pos2);
}

// king check

bool Board::king_check(pair<int, int> pos1, pair<int, int> pos2) {
    if (if_place_to_own_piece(pos1, pos2)) return false; 

    int row_diff = abs(pos1.first - pos2.first);
    int col_diff = abs(pos1.second - pos2.second);

    // Check for diagonal move!
    if (row_diff == 1 && col_diff == 1) return true;

    // Check for straight move
    if (row_diff == 1 && col_diff == 0) return true;
    if (row_diff == 0 && col_diff == 1) return true;

    // Check for castling
    if (row_diff == 0 && col_diff == 2) return valid_castling(pos1, pos2);

    return false;
}

bool Board::king_path_clear(pair<int, int> pos1, pair<int, int> pos2) {
    int step = (pos2.second > pos1.second) ? 1 : -1;
    int currentCol = pos1.second + step;
    
    while (currentCol != pos2.second) {
        if (pieces[make_pair(pos1.first, currentCol)]->get_piece_type() != PieceType::EMPTY) {
            return false; 
        }
        currentCol += step;
    }

    return true;
}

bool Board::valid_castling(pair<int, int> pos1, pair<int, int> pos2) {
    int color = pieces[pos1]->getcolor();
    if (isKingcheck(color)) return false;
    auto k = dynamic_pointer_cast<King>(pieces[pos1]);
    if (k->has_king_moved) return false;
    if (!king_path_clear(pos1, pos2)) return false;

    int col_diff = pos2.second - pos1.second;
 
    if (col_diff > 0) { // move to right
        // if is black -> (7,7); if is white (7,0)
        pair<int, int> rookPos = (color == 0) ? make_pair(7, 7) : make_pair(0, 7);
        if (pieces[rookPos] -> get_piece_type() != PieceType::ROOK) return false;
        auto rookPtr = dynamic_pointer_cast<Rook>(pieces[rookPos]);
        if (rookPtr && rookPtr->has_rook_moved) return false;
        if (color == 0) {
            if (ispieceattack(color, make_pair(7, 5))) return false;
        } else if (color == 1) {
            if (ispieceattack(color, make_pair(0, 5))) return false;
        }

    } else if (col_diff < 0) { // move to left
        // if is black -> (7,7); if is white (7,0)
        pair<int, int> rookPos = (color == 0) ? make_pair(7, 0) : make_pair(0, 0);
        if (pieces[rookPos] -> get_piece_type() != PieceType::ROOK) return false;
        auto rookPtr = dynamic_pointer_cast<Rook>(pieces[rookPos]);
        if (rookPtr && rookPtr->has_rook_moved) return false;
        if (color == 0) {
            if (ispieceattack(color, make_pair(7, 3))) return false;
        } else if (color == 1) {
            if (ispieceattack(color, make_pair(0, 3))) return false;
        }
    }

    return true;
}

void Board::notifyall(Pieces &p) {
    if (td && gd) {
        td->notify(p);
        gd->notify(p);
    }
}


bool Board::virtual_check(pair<int, int> pos1, pair<int, int> pos2) {
    Board vb = Board(*this);
    vb.real_place_piece(pos1, pos2);
    return !vb.isKingcheck(pieces[pos1]->getcolor());
}

vector<pair<int, int>> Board::setof_legalmoves(pair<int, int> pos) {
    vector<pair<int, int>> legal_moves;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            auto new_pos = make_pair(i, j);
            Board vb = Board(*this);
            if (vb.place_piece (pos , new_pos)) legal_moves.emplace_back(new_pos);
        }
    }
    return legal_moves;
}

bool Board::check_legal_move(pair<int, int> pos1, pair<int, int> pos2) {
    auto value = pieces[pos1];
    bool piece_check = 0;
    if (value->get_piece_type() == PieceType::KING) {
        piece_check = king_check(pos1, pos2);
    } else if (value->get_piece_type() == PieceType::QUEEN) {
        piece_check = queen_check(pos1, pos2);
    } else if (value->get_piece_type() == PieceType::ROOK) {
        piece_check =rook_check(pos1, pos2);
    } else if (value->get_piece_type() == PieceType::BISHOP) {
        piece_check = bishop_check(pos1, pos2);
    } else if (value->get_piece_type() == PieceType::KNIGHT) {
        piece_check = knight_check(pos1, pos2);
    } else if (value->get_piece_type() == PieceType::PAWN) {
        piece_check = pawn_check(pos1, pos2);

    } else if (value->get_piece_type() == PieceType::EMPTY) {
        piece_check = empty_check(pos1, pos2);
    } 
    return (piece_check && virtual_check(pos1, pos2));
}

bool Board::if_place_to_own_piece(pair<int, int> pos1, pair<int, int> pos2) {
    return pieces[pos1]->getcolor() == pieces[pos2]->getcolor();
}
