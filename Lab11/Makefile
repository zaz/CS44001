compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# "clean" and "test" are not produced by make
.PHONY: clean test

# build files
coffeeShack: coffeeShack.cpp Drink.hpp Barista.hpp Prices.hpp
	$(compiler) $(flags) coffeeShack.cpp Drink.hpp Barista.hpp Prices.hpp \
		-o coffeeShack

# delete built files
clean:
	rm -f coffeeShack

test:
	make coffeeShack
	./coffeeShack
