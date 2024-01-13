#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
class Cell;

class TextDisplay: public Observer {
 public:
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
  TextDisplay(int n);

  //big 5
  TextDisplay(const TextDisplay& other);
  TextDisplay(TextDisplay&& other);
  TextDisplay& operator=(const TextDisplay& other);
  TextDisplay&& operator=(TextDisplay&& other);
  ~TextDisplay();

  void notify(Cell &c) override;
  SubscriptionType subType() override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
