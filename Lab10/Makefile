compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# "clean" and "test" are not produced by make
.PHONY: clean test

# build files
AdapterClass: AdapterClass.cpp
	$(compiler) $(flags) AdapterClass.cpp -o AdapterClass

# delete built files
clean:
	rm -f AdapterClass

test:
	make AdapterClass
	echo -e "3\n4\n" | ./AdapterClass
