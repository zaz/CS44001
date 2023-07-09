//
// sorting apples
// non STL-algorithm code to be replaced by algorthms
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

const double minWeight = 3.;
const double maxWeight = 8.;

struct Apple {
    double weight;  // oz
    string color;   // red or green
    void print() const { cout << color << ", " <<  weight << endl; }
    friend bool operator<(const Apple& left, const Apple& right) {
        return left.weight < right.weight;
    }
};


int main(){
    srand(time(nullptr));

    cout << "Input crate size: ";
    int size;
    cin >> size;

    vector<Apple> crate(size);

    // assign random weight and color to apples in the crate
    // TODO replace with generate()
    for (auto it = crate.begin(); it != crate.end(); ++it) {
        it->weight = minWeight +
            static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        it->color = rand() % 2 == 1 ? "green" : "red";
    }

   // for_each() possibly
    cout << "all apples" << endl;
    for (const auto &e: crate)
        e.print();

    cout << "Enter weight to find: ";
    double toFind;
    cin >> toFind;

    // TODO count_if()
    int cnt = 0;
    for (auto it = crate.cbegin(); it != crate.cend(); ++it)
        if(it->weight > toFind) ++cnt;

    cout << "There are " << cnt << " apples heavier than "
            << toFind << " oz" <<  endl;

    // find_if()
    cout << "at positions ";
    for (int i=0; i < size; ++i)
        if (crate[i].weight > toFind)
            cout << i << ", ";
    cout << endl;

    // max_element()
    double heaviest = crate[0].weight;
    for (int i=1; i < size; ++i)
        if (crate[i].weight > heaviest) heaviest = crate[i].weight;
    cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;

    // for_each() or accumulate()
    double sum = 0;
    for (int i=0; i < size; ++i)
        sum += crate[i].weight;
    cout << "Total apple weight is: " << sum << " oz" << endl;


    // TODO transform();
    cout << "How much should they grow: ";
    double toGrow;
    cin >> toGrow;
    for (unsigned int i=0; i < crate.size(); ++i)
        crate[i].weight += toGrow;

    cout << "Input minimum acceptable weight: ";
    double minAccept;
    cin >> minAccept;

    // removing small apples
    // nested loops, TODO replace with a single loop modification idiom
    // remove_if()
    bool removed;
    do {
        removed = false;
        for (auto it = crate.begin(); it != crate.end(); ++it)
            if (it->weight < minAccept) {
                crate.erase(it);
                removed = true;
                break;
            }
    } while(removed);
    cout << "removed " << size - crate.size() << " elements" << endl;

    std::sort(crate.begin(), crate.end());

    // for_each() possibly
    cout << "sorted remaining apples" << endl;
    for (const auto &e: crate) {
        e.print();
    }
}
