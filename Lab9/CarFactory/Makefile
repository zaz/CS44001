compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# clean" and "test" are not produced by make
.PHONY: clean test

# build files
CarBuyer: CarBuyer.cpp CarFactory.cpp
	$(compiler) $(flags) CarFactory.cpp CarBuyer.cpp -o CarBuyer

# delete built files
clean:
	rm -f CarBuyer

test:
	make
	./CarBuyer
