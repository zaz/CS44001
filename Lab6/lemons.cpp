//
// Pick the best quality lemons using a priority queue.
//
// Mikhail Nesterenko
// Modified by Zaz Brown
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>

using std::cout; using std::endl;

struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    // random box size
    srand(time(nullptr));
    const int boxSize = rand() % maxBoxSize + 1;

    // randomly generate Lemons:
    std::priority_queue<Lemon> box;
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
