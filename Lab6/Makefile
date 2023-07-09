compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# "all" and clean" are not produced by make
.PHONY: all clean

all: lemons oranges apples peaches

# build files
lemons: lemons.cpp
	$(compiler) $(flags) lemons.cpp -o lemons
oranges: oranges.cpp
	$(compiler) $(flags) oranges.cpp -o oranges
apples: apples.cpp
	$(compiler) $(flags) apples.cpp -o apples
peaches: peaches.cpp
	$(compiler) $(flags) peaches.cpp -o peaches

# delete built files
clean:
	rm -f lemons oranges apples peaches
