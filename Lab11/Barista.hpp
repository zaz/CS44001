#include <iostream>
#include "Drink.hpp"
#include "Prices.hpp"

using std::string;

#ifndef BARISTA_H_
#define BARISTA_H_

class Barista {
public:
    Barista(Barista *successor=nullptr):successor_(successor) {}
    virtual DrinkWithAddition* add(DrinkWithAddition* drink, string addition) {
        if (successor_ != nullptr)
            return successor_->add(drink, addition);
        else {
            std::cerr << "ERROR: Nobody can handle this request.\n"
                      << std::flush;
            return drink;
        }
    }
private:
    Barista *successor_;
};

class JuniorBarista: public Barista {
public:
    JuniorBarista(Barista *successor=nullptr): Barista(successor){}
    DrinkWithAddition* add(DrinkWithAddition* drink, string addition) override {
        std::cout << "As a junior barista, I'm afrad I'm not qualified to add "
                  << addition << " to your drink.\n"
                  << "Fetching a senior barista...\n" << std::flush;
        return Barista::add(drink, addition);
    }
};

class SeniorBarista: public Barista {
public:
    SeniorBarista(Barista *successor=nullptr): Barista(successor){}
    DrinkWithAddition* add(DrinkWithAddition* drink, string addition) override {
        if (addition != "honey") {
            std::cout << "Senior barista adding " << addition
                      << " to your drink.\n" << std::flush;
            return new DrinkWithAddition(drink, addition, prices[addition]);
        } else {
            std::cout << "As a senior barista, I'm afrad I'm not qualified to"
                      << " add " << addition << " to your drink.\n"
                      << "Fetching a manager...\n" << std::flush;
            return Barista::add(drink, addition);
        }
    }
};

class Manager: public Barista {
public:
    Manager(Barista *successor=nullptr): Barista(successor){}
    DrinkWithAddition* add(DrinkWithAddition* drink, string addition) override {
        return new DrinkWithAddition(drink, addition, prices[addition]);
    }
};

#endif // BARISTA_H_
