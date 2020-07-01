# NTU IM DSAP Final Project
## Problem Description
- There will only be 4 walls and 1 point in the simplest map i.e. first stage. New rules will be released when the student passing the first stage. The rule of current second stage is that there will be 4 walls and multi-points, and the grade of each point is different.
- No matter what points the snake eats, the length of snake will only increase by 1 unit.
- The map only changes when snake eats the point.

### Constraints
-  At first stage, there is no any constraint.
-  At second stage, the step limit is 8000 steps and execution time limit is 2 minutes. Also, there will be obstacles in the map.

## Algorithm
### DFS
1. Generate DFS step map (delete current tail while moving)
2. Find nearest ScorePoint. Track path and follow the *whole path*
3. If no valid ScorePoint exists, Move to (Random) *direction*.
* Get 11 Points
* suck. The Map is too big

### BFS
1. Generate BFS step map (delete current tail while moving)
2. Find nearest ScorePoint. Track path and follow the *direction* (can modify to whole path)
3. If no valid ScorePoint exists, Move to (Random) *direction*.
* Get 45 Points
* Kill himself

### A-star

### Greedy
1. Generate BFS step map from real Snake S1. Sort the ScorePoint with step length. Start with nearest ScorePoint, get the virtual snake S2 position (while S1 eat the food). If we can find path from S2's head to its tail. Track this path (P1) and follow the *whole path from S1 to S2*.
2. If there's no ScorePoint valid, Compute the longest path (P2) from S1's head to its tail. follow this path's *first direction*.
3. If no longest path exist, follow the direction that makes S1 the farthest from the food.

### Hamiltonian

## Online Resources
### About Print
* [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code#Terminal_input_sequences)

### About Algorithm
* [chuyangliu / snake](https://github.com/chuyangliu/snake)
* [I Created a PERFECT SNAKE A.I.](https://www.youtube.com/watch?v=tjQIO1rqTBE)
    * [pseudorandomcoder / YouTube / SnakeGame](https://github.com/pseudorandomcoder/YouTube/tree/master/SnakeGame)
* waitingfy.com
    * [waitingfy / snake](https://github.com/waitingfy/snake)
    * [archives](http://www.waitingfy.com/archives/951)

