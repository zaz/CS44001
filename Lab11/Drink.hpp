// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <string>

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
    virtual std::string getFullName() const {
        return getName();
    };
private:
    DrinkSize size_;
    int price_;
};
