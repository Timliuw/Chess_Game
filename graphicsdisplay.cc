#include <iostream>
#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(Xwindow &xw): xw{xw}{ }


void GraphicsDisplay::notify(Pieces &p) {
  int i = p.get_pos().first;
  int j = p.get_pos().second;
  char c = p.get_state();
  auto pos = p.get_pos();
  ostringstream oss{};
  oss << c;
  string s;
  s = oss.str(); //s we actually use
  int color = p.getcolor(); 
  int x = 40 + j * 50;
  int y = 400 - i * 50;
  int rec_color;
  if (color == 0) rec_color = 2;//red
  else if (color == 1) rec_color = 4;//blue
  else if ((i + j) % 2 == 0) rec_color = 1; //white
  else rec_color = 0; //black
  xw.fillRectangle(x, y, 50, 50, rec_color);
  if (c != ' ' && c != '_') {
      xw.drawString(x+25, y+25, s);
  }
}


ostream &operator<<(ostream &out, const GraphicsDisplay &gd) {
  return out;
}

