# file to build
sources = uselist.cpp list.hpp

# file to output
target = uselist

compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# build file
$(target): $(sources)
	$(compiler) $(flags) $(sources) -o $(target)

# delete built file
clean:
	rm -f $(target)

# check if the program compiles and runs without errors
test:
	$(compiler) $(flags) $(sources) -o $(target) && \
	./$(target)
