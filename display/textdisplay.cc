#include <iostream>
#include "textdisplay.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(int n) : theDisplay(), gridSize(n) {
  theDisplay.resize(n, std::vector<char>(n, '_'));
}


void TextDisplay::notify(Cell &c) {
  if (c.getState()) {
    theDisplay[c.getRow()][c.getCol()] = 'X';
  } else {
    theDisplay[c.getRow()][c.getCol()] = '_';
  }
}

TextDisplay::~TextDisplay() {}

SubscriptionType TextDisplay::subType() {
  return SubscriptionType::All;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for(int row = 0; row < td.gridSize;++row) {
    for (int col = 0; col < td.gridSize; ++col) {
      out << td.theDisplay[row][col];
    }
    out << endl;
  }
  return out;
}
