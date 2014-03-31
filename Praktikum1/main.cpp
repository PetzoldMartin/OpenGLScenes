#include "node.h"

#include <iostream>
#include <random>

using namespace std;

const int count = 10;

int main()
{
    Node<int>* root = new Node<int>(0);

    // Random C++ Generator
    default_random_engine generator;
    // with distribution range [count * -1, count]
    uniform_int_distribution<int> distribution(count * -1, count);

    for(int i = count; i >= 0; --i) {
        root->Insert(new Node<int>(distribution(generator)));
    }

    Node<int>::Iterator i(root);
    Node<int>* n = i.previous();

    if(n == NULL) {
        cout << "next not found!" << endl;
    } else {
        cout << "next is: " << n->GetKey() << endl;
    }

    root->Print();
    return 0;
}
