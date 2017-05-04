# lifepp

> A basic implementation of Conway's Game of Life in C++


## Versions

### Current
The program works with an implementation of the `std::vector<std::vector<bool>>` class for the board and the interface uses iostreams to interact. Quite boring yet.

### Upcomping
I guess a version of the board implementing `bool* board[]` is to expect, as I want to dive further into plain C. I might also do a QuadTree or OctTree version if I find the guts to!

Concerning the interface, the next update to come will be a version using the **ncurses** library.

CLI options with `getopt` are on their way too.


## Compile and execute

The repo is set to ignore the files `a.out` and `life`, so you want to use one of these if you compile in the same directory.

Try using:
    g++ main_iostream.cpp board.cpp -std=c++11

or

    g++ main_iostream.cpp board.cpp -std=c++11 -olife

