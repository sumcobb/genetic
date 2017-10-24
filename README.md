# Genetic

Simple genetic algorithm. Initial code from [tolex3](https://github.com/tolex3/genetic).

Makefile builds two executables:

1) run_genetic.exe
2) benchMark.exe

### Genetic evolution

The first program runs a genetic evolution for the problem described in Michell's book "Complexity", i.e the problem is to evolve an algorithm for a "robot" to move around a 10 x 10 grid, with the mission of collecting beer cans, while avoiding making mistakes such as hitting the wall, or trying to pick up cans on an empty square.

The grid contains a random distribution of beer cans, with a probability of ca 50% for any square to contain a can, i.e. there are about 50 cans for each session and each robot.

The robot has limited cognition capabilities, it can only "see" the square it's currently standing on, plus the squares immediately to the North, East, South and West.

Fitness function:
If the robot succeeds in picking up a can on the current square, it is rewarded with 10 points. If it walks into the wall, it receives -5 points in punishment. If it tries to pick up a can on an empty square, it is punished with -1 point.

Maximum theoretical score for a robot is ~500 points ( ~50 cans x 10 points), however, the maximum is not exact since the number of cans in each session is probabilistic. Worst score is -1000 (200 steps x -5 points).

The file constants.h contains the parameters governing the run as follows:

    #define NR_AGENTS 200       // the size of the robot population in each generation
    #define STEPS 200	    // the number of steps the robot takes in each cleaning session
    #define SURVIVORS 20	    // number of survivors in each generation, these become parents for the next
    #define GENERATIONS 10000   // number of generations

From quick test runs of the run_generic.exe program, setting GENERATIONS to 100 or so executes within a minute or so. In order to find a good algorithm to the can picking problem, I suggest setting GENERATIONS to 10000, which on my machine takes some 100 minutes to execute.

### Visualization

The second program runs a visualization of a few different strategies:
* Randomly generated strategy (the initial strategy for all agents in first generation is randomly generated)
* 100 generations of evolution
* 1000 generations of evolution
* 10000 generations of evolution
* 50000 generation of evolution
* 100000 generations of evolution

In order to run the second program, I suggest changing the constant STEPS in constants.h initially to something like 20 - the visualization proceeds step-by-step by the user hitting a key, (any key) and its a bit painful to watch the early generations constantly hitting the wall.

In the top left corner of the screenshot, you see the 10x10 grid.  The  capital "O"'s represent cans to be collected, the "X" represents the robot's current position, the "."'s represent squares visited by the robot, and the lower case "o" represents a square the robot has visited, but where it failed to pick up a can.  The "X" changes temporarily to a "*" when the robot picks up a can.

The star-formed set of numbers represent the robot's current context, i.e the area it currently can observe, i.e. it's current, northern, eastern, southern and western neighboring squares.  The numbers indicate as follows:
* 0, wall
* 1, empty
* 2, contains a can

"Coding" refers to the section of the robot's DNA that will determine what action it should take when in this context - from a technical point of view, that number is an index into the strategy array of actions, where each possible context has a defined action. It is this array that is initially randomly generated, and then gradually evolved by mating and mutation over the generations.

"Action" indicates what the robot's DNA (the action entry at the current index in the DNA array) instructs it to do when encountering this particular context. The actions are:
* 0, move north
* 1, move east
* 2, move south
* 3, move west
* 4, pick up
* 5, do nothing
* 6, move in random direction (N,E,S,W)

The bottom heading indicates which of the 6 sample strategies the visualization program is currently running.

The two programs communicate by saving the winning strategy from run_generic to the file array.txt. The second program benchmarkWinningStrategy then reads this information from the file.

## Build

Built running cygwin and the gnu c++ compiler. The second program uses ncurses library for display, which is part of the cygwin distribution, if you've installed the full cygwin distribution. If your ncurses libraries reside in some other place than the cygwin std, you need to change the makefile accordingly.

To build the either program, type `make run_genetic` or `make benchmarkWinningStrategy`.

To build both, type `make all`

    ~/genetic
    $ make all
    g++    -c -o run_genetic.o run_genetic.cpp
    g++    -c -o context.o context.cpp
    g++    -c -o strategy.o strategy.cpp
    g++    -c -o robby.o robby.cpp
    g++    -c -o strategyStore.o strategyStore.cpp
    g++ run_genetic.cpp context.cpp strategy.cpp robby.cpp strategyStore.cpp -o run_genetic.exe
    g++ -I/usr/include/ncurses benchmarkWinningStrategy.cpp context.cpp strategy.cpp
    robby.cpp -lncurses -o benchMark.exe
