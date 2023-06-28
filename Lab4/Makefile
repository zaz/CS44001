# file to build
sources = roster.cpp

# file to output
target = roster

compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# build file
$(target): $(sources)
	$(compiler) $(flags) $(sources) -o $(target)


# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target) rosterObject

# check if the program compiles and runs without errors or memory leaks
test:
	$(compiler) $(flags) $(sources) -o $(target)
	valgrind --leak-check=full --error-exitcode=1 --quiet \
	         --show-possibly-lost=no \
	         ./$(target) test/cs[1-4].txt test/dropouts.txt
