#include <iostream>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay() : MyDisplay() {
  //does nothing, init is done by board_init
}

void TextDisplay::notify(Pieces &p) {
    char c = p.get_state();
    if (p.get_piece_type() != PieceType::EMPTY) {
      cells[p.pos] = c;
    } else {
      int row = p.pos.first;
      int col = p.pos.second;
      if ((row+col) % 2 == 0) cells[p.pos] = '_';
      else cells[p.pos] = ' ';
    }
}

TextDisplay::~TextDisplay() {}


ostream &operator<<(ostream &out, TextDisplay const &td) {
  for(int row = 0; row < td.gridSize;++row) {
    out << 8 - row << " ";
    for (int col = 0; col < td.gridSize; ++col) {
      out << td.cells.at(make_pair(7-row, col));
    }
    out << endl;
  }
  out << endl << "  abcdefgh" <<endl;
  return out;
}
