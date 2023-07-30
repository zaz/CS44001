// Mikhail Nesterenko
// Modified by Zaz Brown

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

const unsigned int initialLotSize = 8;

class CarLot{
public:
   CarLot();
   Car *testDriveCar(){return cars4sale_[0];}

   // if a car is bought, requests a new one
   Car *buyCar(){
      Car *bought = cars4sale_[0];
      cars4sale_[0] =
        factories_[rand()%factories_.size()]->requestCar();
      return bought;
   }

   unsigned int lotSize() const {return cars4sale_.size();}

   Car* replenishCar() {
      return factories_[rand() % factories_.size()] -> requestCar();
   }

private:
   vector<Car*> cars4sale_; // single car for sale at the lot
   vector<CarFactory *> factories_;
};


CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale
   cars4sale_.resize(initialLotSize);
   std::generate_n(cars4sale_.begin(), initialLotSize,
                   [this](){return replenishCar();});
}



CarLot *carLotPtr = nullptr; // global pointer instantiation

// test-drives a car
// buys it if Toyota
void toyotaLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar();

   cout << "Jill Toyoter" << id << endl;
   cout << "test driving "
        << toBuy->getMake() << " "
        << toBuy->getModel();

   if (toBuy->getMake() == "Toyota"){
      cout << " love it! buying it!" << endl;
      carLotPtr -> buyCar();
   } else
      cout << " did not like it!" << endl;
}

// test-drives a car
// buys it if Ford
void fordLover(int id){
   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   Car *toBuy = carLotPtr -> testDriveCar();

   cout << "Jack Fordman " << id << endl;
   cout << " test driving "
        << toBuy->getMake() << " "
        << toBuy->getModel();

   if (toBuy->getMake() == "Ford"){
      cout << " love it! buying it!" << endl;
      carLotPtr -> buyCar();
   } else
      cout << " did not like it!" << endl;
}



int main() {
   srand(time(nullptr));

   const int numBuyers=20;
   for(int i=0; i < numBuyers; ++i)
      if(rand()% 2 == 0)
         toyotaLover(i);
      else
         fordLover(i);

}
