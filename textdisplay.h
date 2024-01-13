#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include "mydisplay.h"
class Cell;
using namespace std;
class TextDisplay: public MyDisplay {
 public:
  int gridSize = 8;
  map<pair<int,int> , char> cells;
  TextDisplay();
  //big 5
  // TextDisplay(const TextDisplay& other);
  // TextDisplay(TextDisplay&& other);
  // TextDisplay& operator=(const TextDisplay& other);
  // TextDisplay&& operator=(TextDisplay&& other);
  ~TextDisplay();
  
  void notify(Pieces& p) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
