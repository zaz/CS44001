// Coffee Shack
// Zaz Brown

#include <iostream>
#include <vector>
#include <deque>
#include "Drink.hpp"
#include "Barista.hpp"

unsigned int nCustomers = 4;

Drink* serveNextCustomer(Barista* barista) {
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

    DrinkWithAddition* drink = new DrinkWithAddition(baseDrink);

    char ingredient;
    do {
        std::cout << "Would you like to add [s]ugar, [c]ream, [h]oney, or [d]one? ";
        std::cin >> ingredient;
        switch (ingredient) {
            case 's':
                drink = barista->add(drink, "sugar");
                break;
            case 'c':
                drink = barista->add(drink, "cream");
                break;
            case 'h':
                drink = barista->add(drink, "honey");
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
    drink->setCustomerName(name);
    Customer* customer = new Customer(name);
    barista->registerCustomer(customer);

    return drink;
}

int main() {
    // set up the Chain of Command
    // barista is the junior barista doing most of the work
    // she temporarily defers to more senior baristas for the more complicated
    // tasks such as adding sugar to coffee
    Barista* barista = new JuniorBarista(new SeniorBarista(new Manager));

    std::deque<Drink*> drinks;

    for (unsigned int i = 0; i < nCustomers;) {
        if (!drinks.empty() && rand() % 2 == 0) {
            barista->notifyCustomers(drinks.front());
            drinks.pop_front();
        } else {
            drinks.push_back(serveNextCustomer(barista));
            i++;
        }
        std::cout << std::endl;
    }
    // once no more customers are in line, serve the rest of the drinks
    while (!drinks.empty()) {
        barista->notifyCustomers(drinks.front());
        drinks.pop_front();
    }

    return 0;
}
