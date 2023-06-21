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
	rm -f $(target) testCollection

test:
# check if the program compiles and runs without errors
	$(compiler) $(flags) $(sources) -o $(target) && ./$(target)
# run testCollection
	$(compiler) $(flags) testCollection.cpp -o testCollection && ./testCollection
