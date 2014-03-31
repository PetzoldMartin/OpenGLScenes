#include "node.h"

#include <iostream>
#include <random>

using namespace std;

const int count = 1000;

int main()
{
    Node<float>* root = new Node<float>(0);

    // Random C++ Generator
    default_random_engine generator;
    // with distribution range [count * -1, count]
    uniform_int_distribution<int> distribution(count * -1, count);

    for(int i = count; i >= 0; --i) {
        root->Insert(new Node<float>(distribution(generator)));
    }

    root->Print();
    return 0;
}
