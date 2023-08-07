compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# "clean", "test", and "all" are not produced by make
.PHONY: clean test all

# default: build all
all: coffeeShack coffeeShackConcurrent

# build files
coffeeShack: coffeeShack.cpp Drink.hpp Barista.hpp Prices.hpp
	$(compiler) $(flags) coffeeShack.cpp -o coffeeShack

coffeeShackConcurrent: coffeeShackConcurrent.cpp Drink.hpp Barista.hpp Prices.hpp
	$(compiler) $(flags) coffeeShackConcurrent.cpp -o coffeeShackConcurrent

# delete built files
clean:
	rm -f coffeeShack coffeeShackConcurrent

test:
	make all
	tests/coffeeShack.sh
	tests/coffeeShackConcurrent.sh
