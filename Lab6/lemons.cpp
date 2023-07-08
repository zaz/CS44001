//
// Pick the best quality lemons using a priority queue.
//
// Mikhail Nesterenko
// Modified by Zaz Brown
//


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;

struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    srand(time(nullptr));
    std::priority_queue<Lemon> box;
    // randomly generate Lemons:
    const int boxSize = rand() % maxBoxSize + 1;
    for (int i = 0; i < boxSize; ++i)
        box.push(Lemon{static_cast<double>(rand()) / RAND_MAX * highestQuality});

    cout << "Here are the lemons (best first): ";

    // print each element in the prioroity queue
    while (!box.empty()) {
        cout << box.top().quality << ", ";
        box.pop();
    }

    cout << endl;
}
