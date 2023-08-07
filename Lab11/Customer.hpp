#include "Drink.hpp"

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

class Customer {
public:
    Customer(std::string name): name_(name) {}
    void notify(Drink* drink) const {
        if (drink->getCustomerName() != name_)
            return;
        std::cout << name_ << " received " << drink->getDescription() << '\n'
                  << std::flush;
    };
    std::string name_;
};

#endif // CUSTOMER_H_
