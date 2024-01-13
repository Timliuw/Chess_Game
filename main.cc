#include "match.h"
#include "textdisplay.h"
using namespace std;

int main(){
    TextDisplay td;
    Xwindow xw;
    GraphicsDisplay gd(xw);
    Board b{&td, &gd};
    b.board_init(&td, &gd);
    std::cout << *(b.td);
    Match match(&b);
    match.interpreter();
    return 0;
}
