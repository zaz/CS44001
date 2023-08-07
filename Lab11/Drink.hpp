// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <string>
#include <iostream>

std::string drinkType = "coffee";

enum class DrinkSize {small, medium, large};

class Drink{
public:
    Drink(DrinkSize size=DrinkSize::small): size_(size) {
        switch(size_){
            case DrinkSize::small:  price_ = 5; break;
            case DrinkSize::medium: price_ = 7; break;
            case DrinkSize::large: price_ = 10; break;
        }
    }
    virtual int getPrice() const { return price_; };
    virtual std::string getSize() const {
         switch(size_){
             case DrinkSize::small: return "small";
             case DrinkSize::medium: return "medium";
             case DrinkSize::large: return "large";
         }
         return "ambiguously sized";
    };
    virtual std::string getName() const {
        return getSize() + " " + drinkType;
    };
    // this allows arbitrary additions such as "with sugar", "honey", "decaf"
    virtual std::string getDescription() const {
        return getName();
    };
    virtual void setCustomerName(std::string name) {
        customerName_ = name;
    };
    virtual std::string getCustomerName() const {
        return customerName_;
    };
private:
    DrinkSize size_;
    int price_;
    std::string customerName_;
};

class DrinkWithAddition: public Drink {
public:
    // include the trivial case, a drink with no addition
    DrinkWithAddition(Drink* drink):
        drink_(drink), addition_(""), extraCost_(0) {}
    DrinkWithAddition(Drink* drink, std::string addition, int cost):
        drink_(drink), addition_(" + " + addition), extraCost_(cost) {}
    int getPrice() const override { return drink_->getPrice() + extraCost_; };
    std::string getDescription() const override {
        return drink_->getDescription() + addition_;
    };
private:
    Drink* drink_;
    std::string addition_;
    int extraCost_;
};