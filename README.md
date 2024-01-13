# CS246-Chess-Project

**Summary**
In our chess game project, the orchestration of gameplay is managed through the interplay of three main components:
the Match object, the Board class, and the MyDisplay object, integrated via the Observer pattern. The Match object
serves as the central hub, interpreting user inputs and connecting them to Player objects, thereby translating these
inputs into moves on the Board. The Board, in turn, is responsible for maintaining the game state and validating the
legality of moves. The implementation of the Observer pattern is pivotal, enabling MyDisplay to receive updates about
game state changes and reflect these in both graphical and text-based displays. This design ensures a dynamic,
responsive, and accurate representation of the game, providing a robust and interactive chess experience.

**Some Bonus Feature in our chess game:**
Memory Management with Smart Pointers: The game employs unique_ptr and shared_ptr for efficient memory
management. The unique_ptr is used to manage the player/human/computer objects, ensuring that these pointers
always refer to their designated objects without the possibility of alteration. In contrast, shared_ptr is utilized for the
chess pieces, with pieces being a superclass that includes subclasses like queen, pawn, king, etc. The advantage here
is the elimination of the need for manual new and delete operations, as shared_ptr automatically deallocated memory
when it goes out of scope.

Draw Condition Feature: The game includes a feature to check for draw conditions. A draw is considered if certain
pieces like bishops and knights remain on the board, among other conditions. This feature enhances the game by
adding realistic endgame scenarios.

Level 4 Computer Intelligence: The third feature is the advanced Level 4 for the computer player. This evaluates each
move based on the point value associated with the chess pieces. For example, the queen, valued at 9 points, is
prioritized over the rook, valued at 5 points. This strategic point-based system enables the computer to make moves
that maximize its advantage, making it a more challenging opponent.

**How to run the code?**
• game white-player black-player starts a new game. The parameters white-player and black-player
can be either human or computer[1-4].
• resign concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a
game.
• A move consists of the command move, followed by the starting and ending coordinates of the piece to be moved. For
example: move e2 e4. Castling would specified by the two-square move for the king: move e1 g1 or move e1
c1 for white. Pawn promotion would additionally specify the piece type to which the pawn is promoted: move e7
e8 Q. In the case of a computer player, the command move (without arguments) makes the computer player make a
move.
• setup enters setup mode, within which you can set up your own initial board configurations. This can only be done
when a game is not currently running. Within setup mode, the following language is used:
– + K e1 places the piece K (i.e., white king in this case) on the square e1. If a piece is already on that square, it
is replaced. The board should be redisplayed.
– - e1 removes the piece from the square e1 and then redisplays the board. If there is no piece at that square, take
no action.
– = colour makes it colour’s turn to go next.
– done leaves setup mode.
