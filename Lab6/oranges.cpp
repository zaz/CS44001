//
// Selecting oranges using multimaps.
//
// Mikhail Nesterenko
// Modified by Zaz Brown
//


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using std::cout; using std::endl;
using std::string;

const int maxNumber = 100;

enum class Variety {orange, pear, apple};
std::vector<string> colors = {"red", "green", "yellow"};

int main(){
    // random number of fruit
    srand(time(nullptr));
    const int numberOfFruit = rand() % maxNumber + 1;

    // randomly generate colored fruits:
    std::multimap<Variety, string> tree;
    for (int i = 0; i < numberOfFruit; ++i) {
        tree.emplace(static_cast<Variety>(rand() % 3),  // random variety
                     colors[rand()%3]);                 // random color
    }

    cout << "Colors of the oranges: ";
    std::for_each(tree.lower_bound(Variety::orange),
                  tree.upper_bound(Variety::orange),
                  [](auto orangeColor) { cout << orangeColor.second << ", "; } );
    cout << endl;
}
