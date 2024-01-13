#ifndef MYDISPLAY_H
#define MYDISPLAY_H

#include "pieces.h"

class Pieces;
// abstract observer
// no implementation
class MyDisplay {
 public:
  virtual void notify(Pieces &p) = 0;
};
#endif
