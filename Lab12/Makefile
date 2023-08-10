compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# "clean", "test", and "all" are not produced by make
.PHONY: clean test all

# default: build all
all: genealogy

# build files
genealogy: genealogy.cpp
	$(compiler) $(flags) genealogy.cpp -o genealogy

# delete built files
clean:
	rm -f genealogy

test: genealogy
	./genealogy
