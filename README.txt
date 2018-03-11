LC Chen and Alycia Lee

1. Describe how and what each group member contributed for the past two weeks.
Alycia:
- Made and committed changes to GitHub
- Filled in Player() and doMove() functions
- Attempted minimax

LC:
- Filled in Player() and doMove() functions
- Implemented heuristic strategy

2. Document the improvements that your group made to your AI to make it tournament-worthy. Explain why you think your strategy(s) will work. 

We attempted to implement minimax, but given the time we had before Assignment 9 Part 1 was due, we were unable to get a working version of the minimax function. In terms of the heuristic strategy, we iterated through the board and ranked the value of each position on the board in terms of how many points could be obtained if the next player chose the move best for them. Then, we coded our AI to choose the (legal) move with the highest value. (Most optimal for our AI). This was relatively straightforward because an Othello board has fixed optimal board locations. 
