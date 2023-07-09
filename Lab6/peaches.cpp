//
// Jamming peaches using algorithms.
//
// Mikhail Nesterenko
// Modified by Zaz Brown
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Peaches{
   double weight;  // oz
   bool ripe;      // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};


int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   unsigned int size;
   cin >> size;

   vector<Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   generate(basket.begin(), basket.end(), [minWeight, maxWeight](){
      Peaches p;
      p.weight = minWeight +
            static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      p.ripe = rand() % 2;
      return p;
   });

   // for_each() possibly
   cout << "all peaches"<< endl;
   for(const auto &e: basket) {
      e.print();
   }

   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   for(auto it=basket.begin(); it != basket.end();)
      if(it->ripe){
	 peck.push_front(std::move(*it));
	 it=basket.erase(it);
      }else
	 ++it;

   // for_each() possibly
   cout << "peaches remainng in the basket"<< endl;
   for(const auto &e: basket) {
      e.print();
   }

   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   for(const auto &e: peck) {
      e.print();
   }


   // prints every "space" peach in the peck
   const int space=3;
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;

   // replace with advance()/next()/distance()
   // no explicit iterator arithmetic
   auto it=peck.cbegin(); int i = 1;
   while(it != peck.cend()){
      if(i == space){
	 it->print();
	 i=0;
      }
      ++i;
      ++it;
   }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = 0;
   for(auto it=peck.begin(); it != peck.end();)
      if(it->weight < weightToJam){
	 jamWeight += it->weight;
	 it=peck.erase(it);
      }else
	 ++it;

   cout << "Weight of jam is: " << jamWeight << endl;

}

