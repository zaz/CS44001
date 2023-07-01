# file to build
sources = roster.cpp

# file to output
target = roster

arguments = test/cs[1-4].txt test/dropouts.txt

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

test:
# Check if the program compiles and runs without errors or memory leaks. Regular
# program output is discarded, but stderr from Valgrind and program is printed.
	$(compiler) $(flags) $(sources) -o $(target)
	valgrind --leak-check=full --error-exitcode=1 --quiet \
	         --show-possibly-lost=no ./$(target) $(arguments) >/dev/null
# check that program output matches expected output
	diff -U 3 test/roster.out <(./$(target) $(arguments))
