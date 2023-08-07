// Coffee Shack
// Zaz Brown

#include <iostream>
#include "Drink.hpp"

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

    // I'm using pointers and new statements
    // I hope you're proud of me
    Drink* baseDrink = new Drink(myDrinkSize);

    DrinkWithAddition* myDrink = new DrinkWithAddition(baseDrink);

    char ingredient;
    do {
        std::cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
        std::cin >> ingredient;
        switch (ingredient) {
            case 's':
                myDrink = new DrinkWithAddition(myDrink, "sugar", 1);
                break;
            case 'c':
                myDrink = new DrinkWithAddition(myDrink, "cream", 2);
                break;
            case 'h':
                myDrink = new DrinkWithAddition(myDrink, "honey", 3);
                break;
            case 'd':
                break;
            default:
                std::cout << "Sorry, we don't have that ingredient." << std::endl;
                return 1;
        }
    } while (ingredient != 'd');

    std::cout << "Can I get your name? ";
    std::string name;
    std::cin >> name;
    myDrink->setCustomerName(name);

    std::cout << myDrink->getCustomerName()
              << ", your "
              << myDrink->getDescription()
              << " is ready. It will be $"
              << myDrink->getPrice()
              << ", please."
              << std::endl;
}
