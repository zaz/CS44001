# file to build
sources = wordCount.cpp

# file to output
target = wordCount

compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# build file
wordCount: wordCount.cpp
	$(compiler) $(flags) $(sources) -o $(target)

# delete built file
clean:
	rm -f $(target)

# check if the program compiles and runs without errors
test:
	$(compiler) $(flags) $(sources) -o $(target) && \
	diff -U 3 <(./$(target) test.txt) <(cat testOutput.txt)
