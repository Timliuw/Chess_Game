#include "computer.h"

Computer::Computer(Board* board, int color, int level) : Player{board, color}, level{level}{}

pair<pair<int, int>, pair<int, int>> Computer::generate_move(){
        cout<<"Computer Player Activated"<<endl;

        vector<pair<pair<int, int>, pair<int, int>>> legal_moves;

        for (auto[key , value] : board->pieces){
            if (value->color == color) {
                vector<pair<int, int>> moves = board->setof_legalmoves(key);
                // add all moves to legal_moves with starting and ending position
                for (pair<int, int> move : moves) {
                    legal_moves.push_back(make_pair(key, move));
                }
            }
        }
        
        if (level == 1) {
            // generate random number between 0 and legal_moves.size()
            int random_index = rand() % legal_moves.size();
            // return the move at that index
            return legal_moves[random_index];
        } else if (level == 2) {
            // generate capturing moves
            vector<string> capturing_moves;
            for (pair<pair<int,int>, pair<int,int>> move : legal_moves) {
                if (board->is_capturing(move)) {
                    return move;
                }
            }
            int random_index = rand() % legal_moves.size();
            // return the move at that index
            return legal_moves[random_index];
        } else if (level == 3) {
            // generate capturing avoiding moves
            vector<string> capturing_avoiding_moves;
            for (pair<pair<int,int>,pair<int,int>> move : legal_moves) {
                if (!board->is_capturing(move)) {
                    return move;
                }
            }
            int random_index = rand() % legal_moves.size();
            // return the move at that index
            return legal_moves[random_index];
        } else if (level == 4) {
            // generate move that creates the largest difference in points of materials on the board
            int max = 0;
            pair<pair<int,int>,pair<int,int>> best_move;
            for (pair<pair<int,int>,pair<int,int>> move : legal_moves) {
                int points = board->points_of_material(move);
                if (points > max) {
                    max = points;
                    best_move = move;
                }
            }

            if (max == 0) {
                int random_index = rand() % legal_moves.size();
                // return the move at that index
                return legal_moves[random_index];
            }
            
            return best_move;
        } else {
            string error = "Invalid level";
            throw std::invalid_argument(error);
        }
    };
