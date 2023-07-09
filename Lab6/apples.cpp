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
#include <numeric>

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
    generate(crate.begin(), crate.end(), []() {
        Apple a;
        a.weight = minWeight +
            static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        a.color = rand() % 2 == 1 ? "green" : "red";
        return a;
    });

    cout << "all apples" << endl;
    for (const auto &e: crate)
        e.print();

    cout << "Enter weight to find: ";
    double toFind;
    cin >> toFind;

    int cnt = count_if(crate.cbegin(), crate.cend(), [toFind](const Apple &a) {
        return a.weight > toFind;
    });

    cout << "There are " << cnt << " apples heavier than "
         << toFind << " oz" << endl;

    cout << "at positions ";
    for (int i=0; i < size; ++i)
        if (crate[i].weight > toFind)
            cout << i << ", ";
    cout << endl;

    cout << "Heaviest apple weighs: "
         << max_element(crate.cbegin(), crate.cend())->weight
         << " oz" << endl;;

    cout << "Total apple weight is: "
         << std::accumulate(crate.cbegin(), crate.cend(), 0.0,
                            [](double sum, const Apple &a) {
                                return sum + a.weight;
                            })
         << " oz" << endl;


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
