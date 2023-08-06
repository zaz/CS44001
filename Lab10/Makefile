compiler = g++

# compiler flags
flags = -Wall -Wextra -std=c++17

# "clean", "test", and "all" are not produced by make
.PHONY: clean test all

all: AdapterClass stateTransitions prototypeScheduler

# build files
AdapterClass: AdapterClass.cpp
	$(compiler) $(flags) AdapterClass.cpp -o AdapterClass

stateTransitions: stateTransitions.cpp
	$(compiler) $(flags) stateTransitions.cpp -o stateTransitions

prototypeScheduler: prototypeScheduler.cpp
	$(compiler) $(flags) prototypeScheduler.cpp -o prototypeScheduler

# delete built files
clean:
	rm -f AdapterClass stateTransitions prototypeScheduler

test:
	make AdapterClass
	echo -e "3\n4\n" | ./AdapterClass
