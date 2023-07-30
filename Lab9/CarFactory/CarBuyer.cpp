// Mikhail Nesterenko
// Modified by Zaz Brown

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "CarFactory.hpp"

using std::vector;
using std::cout; using std::endl;

const int numBuyers = 20;
const unsigned int initialLotSize = 8;
const vector FordModels = {"Focus", "Mustang", "Explorer", "F-150"};
const vector ToyotaModels = {"Corolla", "Camry", "Prius", "4Runner", "Yaris"};

class CarLot {
public:
   CarLot();
   Car* testDriveCar(){return cars4sale_[currentCar_];}

   // if a car is bought, requests a new one
   Car* buyCar() {
      Car* bought = cars4sale_[currentCar_];
      cars4sale_[currentCar_] = replenishCar();
      currentCar_ = 0;
      return bought;
   }

   unsigned int lotSize() const {return cars4sale_.size();}

   Car* replenishCar() {
      return factories_[rand() % factories_.size()] -> requestCar();
   }

   void nextCar() {
      currentCar_ = (currentCar_ + 1) % cars4sale_.size();
   }

private:
   vector<Car*> cars4sale_;  // cars for sale at the lot
   unsigned int currentCar_;  // the car being test driven
   vector<CarFactory*> factories_;
};


CarLot::CarLot() {
   // creates 2 Ford factories and 2 Toyota factories
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());

   // gets the first car for sale
   cars4sale_.resize(initialLotSize);
   std::generate_n(cars4sale_.begin(), initialLotSize,
                   [this](){return replenishCar();});

   currentCar_ = 0;
}


CarLot *carLotPtr = nullptr; // global pointer instantiation

std::string getRidiculousNameForBuyer(std::string make, std::string model) {
   std::string name = "";

   if (make.back() == 'a')
      name = make + "nio ";
   else
      name = make + "anio ";

   if (model.back() == 's')
      name += model + "on";
   else
      name += model + "son";

   return name;
}

// test-drives a car
// buys it if it is make
void carLover(int id, std::string make, std::string model) {
   std::string name = getRidiculousNameForBuyer(make, model);

   if (carLotPtr == nullptr)
      carLotPtr = new CarLot();

   cout << id << ' ' << name << endl;

   for (unsigned int i = 0; i < carLotPtr->lotSize(); ++i) {
      Car *toBuy = carLotPtr -> testDriveCar();

      cout << "  test driving "
           << toBuy->getMake() << " "
           << toBuy->getModel();

      if (toBuy->getMake() == make && toBuy->getModel() == model) {
         cout << " love it! buying it!" << endl;
         carLotPtr -> buyCar();
         break;
      } else {
         cout << " did not like it!" << endl;
         carLotPtr -> nextCar();
      }
   }
}


int main() {
   srand(time(nullptr));

   for(int i=0; i < numBuyers; ++i)
      if(rand()% 2 == 0)
         carLover(i, "Toyota", ToyotaModels[rand()%ToyotaModels.size()]);
      else
         carLover(i, "Ford", FordModels[rand()%FordModels.size()]);
}
