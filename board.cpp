#include "board.hpp"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

int Board::findWeight(Move *m){
    int score;
    if(((m->getX()) == 0 && (m->getY()) == 7)||(m->getY() == 0 && 
            m->getX() == 7)){
        score = 10000;
    }
    else if(((m->getX() == 1 || m->getX() == 6) && (m->getY() == 0)) 
        || ((m->getY() == 1 || m->getY() ==6) && (m->x == 0))){
        score = -5000;
    }
    else if(((m->getX() == 1) || (m->getX() == 6)) && ((m->getY() == 0) || (m->getY() == 7))){
        score = -3000;
    }
    else if(((m->getY() == 1) || (m->getY() == 6)) && ((m->getX() == 0) || (m->getX() == 7))){
        score = -3000;
    }
    else if(((m->getX() == 2) || (m->getX() == 5)) && ((m->getY() == 0) || (m->getY() == 7))){
        score = 1000;
    }
    else if(((m->getY() == 2) || (m->getY() == 5)) && ((m->getX() == 0) || (m->getX() == 7))){
        score = 1000;
    }
    else if(((m->getY() == 3) || (m->getY() == 4)) && ((m->getX() == 0) || (m->getX() == 7))){
        score = 800;
    }
    else if(((m->getX() == 3) || (m->getX() == 4)) && ((m->getY() == 0) || (m->getY() == 7))){
        score = 800;
    }
     else if(((m->getX() == 1) || (m->getX() == 6)) && ((m->getY() == 2) || (m->getY() == 5))){
        score = -450;
    }
    else if(((m->getY() == 1) || (m->getY() == 6)) && ((m->getX() == 2) || (m->getX() == 5))){
        score = -450;
    }
    else if(((m->getX() == 1) || (m->getX() == 6)) && ((m->getY() == 3) || (m->getY() == 4))){
        score = -500;
    }
    else if(((m->getY() == 1) || (m->getY() == 6)) && ((m->getX() == 3) || (m->getX() == 4))){
        score = -500;
    }
    else if(((m->getX() == 2) || (m->getX() == 5)) && ((m->getY() == 2) || (m->getY() == 5))){
        score = 30;
    }
    else if(((m->getY() == 2) || (m->getY() == 5)) && ((m->getX() == 2) || (m->getX() == 5))){
        score = 30;
    }
    else if(((m->getX() == 3) || (m->getX() == 4)) && ((m->getY() == 2) || (m->getY() == 5))){
        score = 10;
    }
    else if(((m->getY() == 3) || (m->getY() == 4)) && ((m->getX() == 2) || (m->getX() == 5))){
        score = 10;
    }
    else if(((m->getX() == 3) || (m->getX() == 4)) && ((m->getY() == 3) || (m->getY() == 4))){
        score = 50;
    }
    return score;
}
/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}
