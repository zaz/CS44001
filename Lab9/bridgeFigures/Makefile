compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# "clean" and "test" are not produced by make
.PHONY: clean test

# build files
bridgeFigures: bridgeFigures.cpp
	$(compiler) $(flags) bridgeFigures.cpp -o bridgeFigures

# delete built files
clean:
	rm -f bridgeFigures

test:
	make bridgeFigures
	echo -e "#\n#\nf\n4\n" | ./bridgeFigures
	echo -e "#\n.\nh\n4\n" | ./bridgeFigures
	echo -e "#\n.\nm\n4\n" | ./bridgeFigures
	echo -e "#\n.\nr\n4\n" | ./bridgeFigures
