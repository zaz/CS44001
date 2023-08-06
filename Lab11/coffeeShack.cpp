#include <iostream>
#include "Drink.hpp"

// A "Coffee Shack" serves coffee to its customers that is composed of the base
// coffee: large ($10), medium ($7) or small ($5) and added ingredients:
// sugar ($1), cream ($2) and honey ($3). The ingredients can be added in any
// order and multiple times. Here is an example dialog for the order
// (customer's input is in bold):

// Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee? m
// Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? s
// Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? h
// Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? h
// Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? d
// Can I get your name? Alex

// Alex, your medium coffee with sugar, honey, honey is ready. It will be $14, please.

int main() {
    std::cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or"
              << " [s]mall coffee? ";
    char size;
    std::cin >> size;

    DrinkSize myDrinkSize;
    switch (size) {
        case 'l':
            myDrinkSize = DrinkSize::large;
            break;
        case 'm':
            myDrinkSize = DrinkSize::medium;
            break;
        case 's':
            myDrinkSize = DrinkSize::small;
            break;
        default:
            std::cout << "Sorry, we don't have that size." << std::endl;
            return 1;
    }

    Drink myDrink(myDrinkSize);

    std::cout << myDrink.getName()
              << " is ready. It will be $"
              << myDrink.getPrice()
              << ", please."
              << std::endl;
}
