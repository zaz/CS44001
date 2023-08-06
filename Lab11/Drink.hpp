// drink class to be used in Coffee Shack lab
// Mikhail Nesterenko
// Modified by Zaz Brown

#include <string>

std::string drinkType = "coffee";

enum class DrinkSize {small, medium, large};

class Drink{
public:
    Drink(DrinkSize size=DrinkSize::small, int price=0):
       size_(size), price_(price) {}
    virtual int getPrice() const { return price_; };
    std::string getSize() const {
         switch(size_){
             case DrinkSize::small: return "small";
             case DrinkSize::medium: return "medium";
             case DrinkSize::large: return "large";
         }
         return "ambiguously sized";
    };
    std::string getName() const {
        return getSize() + " " + drinkType;
    };
private:
    DrinkSize size_;
    int price_;
};
