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
#include <numeric>

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

   cout << "all peaches"<< endl;
   for(const auto &e: basket) {
      e.print();
   }

   deque<Peaches> peck;
   remove_copy_if(basket.begin(), basket.end(), front_inserter(peck),
                  [](const Peaches &p){
      return !p.ripe;
   });

   cout << "peaches remainng in the basket"<< endl;
   for(const auto &e: basket) {
      e.print();
   }
   cout << endl;

   cout << "peaches moved to the peck"<< endl;
   for(const auto &e: peck) {
      e.print();
   }

   // prints every 3rd peach in the peck
   const int space=3;
   cout << "\nevery " << space << "rd peach in the peck" << endl;

   auto times = peck.size()/space;
   auto it = peck.cbegin();
   for (unsigned int i=0; i != times; ++i) {
      it->print();
      advance(it, space);
   }

   // all pecahes bigger than this weight will not be used for jam
   const double weightToJam = 10.0;

   cout << "Weight of jam is: "
        << std::accumulate(peck.begin(), peck.end(), 0.0,
                      [weightToJam](double sum, const Peaches &p){
                         // XXX: I had to add the outer parentheses below.
                         // Does C++ not give precedence to * over + ?
                         return sum + (p.weight * (p.weight < weightToJam));
                        })
        << endl;
}
