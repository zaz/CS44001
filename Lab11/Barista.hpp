#include <iostream>
#include <unordered_set>
#include "Drink.hpp"
#include "Prices.hpp"
#include "Customer.hpp"

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
    void notifyCustomers(Drink* drink) const {
        std::cout << drink->getCustomerName()
                << ", your "
                << drink->getDescription()
                << " is ready. It will be $"
                << drink->getPrice()
                << ", please."
                << std::endl;
        for (auto e: customers_)
            e->notify(drink);
    }
    void registerCustomer(Customer* customer) {
        customers_.insert(customer);
    }
private:
    std::unordered_set <Customer*> customers_;
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
