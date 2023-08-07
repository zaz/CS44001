// Coffee Shack
// Zaz Brown

#include <iostream>
#include <vector>
#include "Drink.hpp"
#include "Barista.hpp"

void drinkReady(Drink* drink) {
    std::cout << drink->getCustomerName()
              << ", your "
              << drink->getDescription()
              << " is ready. It will be $"
              << drink->getPrice()
              << ", please."
              << std::endl;
}

void customerWalksIn() {
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
            exit(1);
    }

    // I'm using pointers and new statements
    // I hope you're proud of me
    Drink* baseDrink = new Drink(myDrinkSize);

    DrinkWithAddition* myDrink = new DrinkWithAddition(baseDrink);

    // set up the Chain of Command
    Barista *barista = new JuniorBarista(new SeniorBarista(new Manager));

    char ingredient;
    do {
        std::cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
        std::cin >> ingredient;
        switch (ingredient) {
            case 's':
                myDrink = barista->add(myDrink, "sugar");
                break;
            case 'c':
                myDrink = barista->add(myDrink, "cream");
                break;
            case 'h':
                myDrink = barista->add(myDrink, "honey");
                break;
            case 'd':
                break;
            default:
                std::cout << "Sorry, we don't have that ingredient." << std::endl;
                exit(1);
        }
    } while (ingredient != 'd');

    std::cout << "Can I get your name? ";
    std::string name;
    std::cin >> name;
    myDrink->setCustomerName(name);

    drinkReady(myDrink);
}

int main() {
    customerWalksIn();
    return 0;
}
