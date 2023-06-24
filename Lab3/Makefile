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
	$(compiler) $(flags) $(sources) -o $(target)
	valgrind --leak-check=full --error-exitcode=1 --quiet \
	         --show-possibly-lost=no ./$(target)
# run testCollection
	$(compiler) $(flags) testCollection.cpp -o testCollection
	valgrind --leak-check=full --error-exitcode=1 --quiet \
	         --show-possibly-lost=no ./testCollection
