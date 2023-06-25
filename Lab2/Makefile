# file to build
sources = wordCount.cpp WordList.cpp WordList.hpp

# file to output
target = wordCount

compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# build file
wordCount: wordCount.cpp
	$(compiler) $(flags) $(sources) -o $(target)

# "clean" and "test" are not produced by make
.PHONY: clean test

# delete built file
clean:
	rm -f $(target)

# check if the program compiles and runs without errors
test:
	$(compiler) $(flags) $(sources) -o $(target) && \
	diff -U 3 <(./$(target) test/1.txt) <(cat test/1.out)
