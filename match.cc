#include "match.h"
using namespace std;
Match::Match(Board* b):board{b} {}

// You interact with the system by issuing text-based commands. The following commands are to be supported:•gamewhite-player  black-playerstarts a new game. The parameterswhite-playerandblack-playercan be eitherhumanorcomputer[1-4].•resignconcedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end agame.•  A move consists of the commandmove, followed by the starting and ending coordinates of the piece to be moved. Forexample:move e2 e4. Castling would specified by the two-square move for the king:move e1 g1ormove e1c1for white.  Pawn promotion would additionally specify the piece type to which the pawn is promoted:move e7e8 Q. In the case of a computer player, the commandmove(without arguments) makes the computer player make amove.•setupenters setup mode, within which you can set up your own initial board configurations.  This can only be donewhen a game is not currently running. Within setup mode, the following language is used:–+ K e1places the pieceK(i.e., white king in this case) on the squaree1. If a piece is already on that square, itis replaced. The board should be redisplayed.–- e1removes the piece from the squaree1and then redisplays the board-> If there is no piece at that square, takeno action.–=colourmakes itcolour’s turn to go next.–doneleaves setup mode.
void Match::interpreter(){
    try{
        unique_ptr<Player> player_one;
        unique_ptr<Player> player_two;
        string command;
        while(cin >> command){
            if(command == "game"){
                string white_player;
                string black_player;
                cin >> white_player;
                cin >> black_player;
                if(white_player == "human"){
                    player_one = make_unique<Human>(board, 1);
                }else if(white_player == "computer1"){
                    player_one = make_unique<Computer>(board, 1, 1);
                }else if(white_player == "computer2"){
                    player_one = make_unique<Computer>(board, 1, 2);
                }else if(white_player == "computer3"){
                    player_one = make_unique<Computer>(board, 1, 3);
                }else if(white_player == "computer4"){
                    player_one = make_unique<Computer>(board, 1, 4);
                }
                if(black_player == "human"){
                    player_two = make_unique<Human>(board, 0);
                }else if(black_player == "computer1"){
                    player_two = make_unique<Computer>(board, 0, 1);
                }else if(black_player == "computer2"){
                    player_two = make_unique<Computer>(board, 0, 2);
                }else if(black_player == "computer3"){
                    player_two = make_unique<Computer>(board, 0, 3);
                }else if(black_player == "computer4"){
                    player_two = make_unique<Computer>(board, 0, 4);
                }
                cout << "A new game has started!" << endl;
            } else if(command == "resign"){
                if(board->turn == true){
                    black_score++;
                } else{
                    white_score++;
                }
                cout << "Game over" << endl;
                // reset board
                board->board_init(board->td, board->gd);

            } else if(command == "move"){
                pair<pair <int, int>, pair<int, int>> move;
                if (board->turn == true) {
                    move = player_one->generate_move();
                } else {
                    move = player_two->generate_move();
                }
                if (board->place_piece(move.first, move.second)) {
                    board->turn = !board->turn;
                    cout<<*board->td;
                    board->set_off_pawn();
                    cout<< "Move successful!" << endl;
                } else {
                    cout <<"Invalid Move"<< endl;
                }

                // check checkmate
                if (board->check_checkmate(board->turn)) {
                    if (board->turn == true) {
                        cout << "Black wins!" << endl;
                        black_score++;
                    } else {
                        cout << "White wins!" << endl;
                        white_score++;
                    }
                    board->board_init(board->td, board->gd);
                    continue;
                }

                // check stalemate
                if (board->check_stalemate(board->turn)) {
                    cout << "Stalemate!" << endl    ;
                    white_score += 0.5;
                    black_score += 0.5;
                    board->board_init(board->td, board->gd);
                    continue;
                }

                // check draw
                if (board->check_draw()) {
                    cout << "Draw!" << endl;
                    white_score += 0.5;
                    black_score += 0.5;
                    board->board_init(board->td, board->gd);
                    continue;
                }
            } else if (command == "setup"){
                cout<< "Setup mode activated!" << endl;
                string setup_command;
                while(cin >> setup_command){
                    if(setup_command == "+"){
                        string piece;
                        string coordinate;
                        cin >> piece;
                        cin >> coordinate;
                        pair <int, int> coordinate_pair = process_coordinate(coordinate);
                        // 0 for black, 1 for white, 2 for empty
                        if (piece == "K"){
                            board->pieces[coordinate_pair] = make_shared<King>(coordinate_pair, 1);
                        } else if (piece == "k"){
                            board->pieces[coordinate_pair] = make_shared<King>(coordinate_pair, 0);
                        } else if (piece == "Q"){
                            board->pieces[coordinate_pair] = make_shared<Queen>(coordinate_pair, 1);
                        } else if (piece == "q"){
                            board->pieces[coordinate_pair] = make_shared<Queen>(coordinate_pair, 0);
                        } else if (piece == "R"){
                            board->pieces[coordinate_pair] = make_shared<Rook>(coordinate_pair, 1);
                        } else if (piece == "r"){
                            board->pieces[coordinate_pair] = make_shared<Rook>(coordinate_pair, 0);
                        } else if (piece == "B"){
                            board->pieces[coordinate_pair] = make_shared<Bishop>(coordinate_pair, 1);
                        } else if (piece == "b"){
                            board->pieces[coordinate_pair] = make_shared<Bishop>(coordinate_pair, 0);
                        } else if (piece == "N"){
                            board->pieces[coordinate_pair] = make_shared<Knight>(coordinate_pair, 1);
                        } else if (piece == "n"){
                            board->pieces[coordinate_pair] = make_shared<Knight>(coordinate_pair, 0);
                        } else if (piece == "P"){
                            board->pieces[coordinate_pair] = make_shared<Pawn>(coordinate_pair, 1);
                        } else if (piece == "p"){
                            board->pieces[coordinate_pair] = make_shared<Pawn>(coordinate_pair, 0);
                        }
                        board->notifyall(*board->pieces[coordinate_pair]);
                        cout<<"Piece added!"<<endl;
                        cout << *board->td;
                    } else if(setup_command == "-"){
                        string coordinate;
                        cin >> coordinate;
                        pair<int, int> coordinate_pair = process_coordinate(coordinate);
                        board->empty_cell(coordinate_pair);
                        board->notifyall(*board->pieces[coordinate_pair]);
                        cout<<"Piece removed!"<<endl;
                        cout << *board->td;
                    } else if(setup_command == "="){
                        string colour;
                        cin >> colour;
                        if(colour == "white"){
                            board->turn = true;
                        }
                        else if(colour == "black"){
                            board->turn = false;
                        }
                        cout<<"Turn changed!"<<endl;
                    } else if(setup_command == "done"){
                        // check if there is only one king for each colour
                        int white_king_count = 0;
                        int black_king_count = 0;
                        for(auto it = board->pieces.begin(); it != board->pieces.end(); ++it){
                            if(it->second->get_piece_type() == PieceType::KING){
                                if(it->second->getcolor() == 1){
                                    white_king_count++;
                                } else{
                                    black_king_count++;
                                }
                            }
                        }

                        if(white_king_count != 1 || black_king_count != 1){
                            cout << "There must be exactly one white king and one black king" << endl;
                            continue;
                        }

                        // check if there is any pawn on the first or last row
                        for(auto it = board->pieces.begin(); it != board->pieces.end(); ++it){
                            if(it->second->get_piece_type() == PieceType::PAWN){
                                if (it->first.first == 0 || it->first.first == 7){
                                    cout << "Pawns cannot be on the first or last row" << endl;
                                    continue;
                                }
                            }
                        }
                        // check if either king is in check
                        for(auto it = board->pieces.begin(); it != board->pieces.end(); ++it){
                            if(it->second->get_piece_type() == PieceType::KING){
                                if(board->isKingcheck(it->second->getcolor())){
                                    cout << "King cannot be in check" << endl;
                                    continue;
                                }
                            }
                        }
                        cout<<"Setup mode deactivated!"<<endl;
                        break;
                    }
                }
            }
        }
    } catch (std::exception& e) {
        cerr << e.what() << endl;
    }

    // output score
    cout << "Final Score:" << endl;
    cout << "White: " << white_score << endl;
    cout << "Black: " << black_score << endl;
}

pair<int, int> Match::process_coordinate(string coordinate){
    int x;
    int y;
    if(coordinate[0] == 'a'){
        x = 0;
    }else if(coordinate[0] == 'b'){
        x = 1;
    }else if(coordinate[0] == 'c'){
        x = 2;
    }else if(coordinate[0] == 'd'){
        x = 3;
    }else if(coordinate[0] == 'e'){
        x = 4;
    }else if(coordinate[0] == 'f'){
        x = 5;
    }else if(coordinate[0] == 'g'){
        x = 6;
    }else if(coordinate[0] == 'h'){
        x = 7;
    }
    y = coordinate[1] - '0' - 1;
    return std::make_pair(y, x);
}
