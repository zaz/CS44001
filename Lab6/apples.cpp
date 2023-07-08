// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 09/26/2022


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
   for(auto it = crate.begin(); it != crate.end(); ++it){
      it->weight = minWeight +
	           static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
      it->color = rand() % 2 == 1 ? "green" : "red";
   }


    // for_each() possibly
   cout << "all appleas"<< endl;
   for(const auto &e: crate) {
      e.print();
   }


   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   int cnt = 0;
   for(auto it = crate.cbegin(); it != crate.cend(); ++it)
      if(it->weight > toFind) ++cnt;

   cout << "There are " << cnt << " apples heavier than "
	<< toFind << " oz" <<  endl;

   // find_if()
   cout << "at positions ";
   for(int i=0; i < size; ++i)
      if(crate[i].weight > toFind)
	 cout << i << ", ";
   cout << endl;


   // max_element()
   double heaviest = crate[0].weight;
   for(int i=1; i < size; ++i)
      if(crate[i].weight > heaviest) heaviest = crate[i].weight;
   cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;


   // for_each() or accumulate()
   double sum = 0;
   for(int i=0; i < size; ++i)
      sum += crate[i].weight;
   cout << "Total apple weight is: " << sum << " oz" << endl;


   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   for(int i=0; i < crate.size(); ++i)
      crate[i].weight += toGrow;

   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;


   // removing small apples
   // nested loops, replace with a single loop modification idiom
   bool removed;
   do{
      removed = false;
      for(auto it = crate.begin(); it != crate.end(); ++it)
	 if(it->weight < minAccept){
	    crate.erase(it);
	    removed = true;
	    break;
       }
   }while(removed);
   cout << "removed " << size - crate.size() << " elements" << endl;


   // bubble sort, replace with sort()
   bool swapped;
   do{
      swapped = false;
      for(int i=0; i < crate.size()-1; ++i)
	 if(crate[i].weight > crate[i+1].weight){
	    std::swap(crate[i], crate[i+1]);
	    swapped = true;
	 }
   }while(swapped);


   // for_each() possibly
   cout << "sorted remaining apples"<< endl;
   for(const auto &e: crate) {
      e.print();
   }

}

