#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
#include <iostream>
#include <vector>
#include "mydisplay.h"
#include "window.h"
#include "pieces.h"
#include <sstream>

class GraphicsDisplay: public MyDisplay {
 public:
  Xwindow &xw;
  GraphicsDisplay(Xwindow &xw);

  //method
  void notify(Pieces &p) override;

  friend std::ostream &operator<<(std::ostream &out, const GraphicsDisplay &gd);
};

#endif
