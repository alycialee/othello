#include "player.hpp"
//Alycia's comment

//LC's contribution
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board();
    color = side;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    Side opponent;
    if(color == WHITE)
    {
        std::cerr << "WHITE" << std::endl;
        opponent = BLACK;
    }
    else
    {
        std::cerr << "BLACK" << std::endl;
        opponent = WHITE;
    }

    if(opponentsMove != nullptr){
        board->doMove(opponentsMove, opponent);
    }
    
    int time = msLeft;

    if(msLeft == -1){
        time = 500000000;
    }
    Move* theMove = nullptr;
    while(time > 0){
        
        if(board->hasMoves(color))
        {
            int max_score = -10;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    Move *move = new Move(i, j);
                    if(board->checkMove(move, color))
                    { 
                        int score = board->findWeight(move);
                        if(score > max_score) {

                            max_score = score;
                            theMove = move;

                            //std::cerr << theMove->getX() << std::endl;
                            //std::cerr << theMove->getY() << std::endl;

                            //std::cerr << "check " << board->checkMove(theMove, color) << std::endl;
                            
                        }
                    }
                    //delete(move);
                }
            }
            board->doMove(theMove, color);
            //std::cerr << theMove->getX() << std::endl;
            //std::cerr << theMove->getY() << std::endl;
            return theMove;
        }
    }
    // while(time > 0)
    // {
    //     x = rand() % 8;
    //     y = rand() % 8;
    //     if(board->hasMoves(color))
    //     {
    //         Move *move = new Move(x, y);
            
    //         if(board->checkMove(move, color))
    //         {
    //             board->doMove(move, color);
    //             return move;
    //         }
    //     }
    // }

    return nullptr;
}
