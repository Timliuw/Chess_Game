#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
class Cell;

class GraphicsDisplay: public Observer {
  Xwindow &xw;
  const int gridSize;
 public:
  GraphicsDisplay(Xwindow &x, int n);

  void notify(Cell &c) override;
  SubscriptionType subType() override;
  void fillRec(int x, int y, int width, int height, int colour);
  ~GraphicsDisplay();

  friend std::ostream &operator<<(std::ostream &out, const GraphicsDisplay &td);
};

#endif
