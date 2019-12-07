//
//  main.cpp
//  CS 251 Project 7 Heap
//
//  Created by Viktor Kirillov on 12/3/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <utility>
#include "minqueue.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
//    minqueue<char, int> mq(10);
    minqueue<int, char> mq(vector<int>{123, 456, 789, 1234, 5678, 91011}, '#');
    vector<pair<int, char> > v = mq.getArr();
    cout << "Array: ";
    for (auto p : v)
        cout << p.first << ":" << p.second << ", ";
    cout << endl;
    
    
    char a; int b;
    while(true) {
        cin >> a;
        if (a == 'p') {
            cin >> a >> b;
            mq.pushinorder(a, b);
        }
        if (a == 'f') {
            cout << "Front: " << mq.minfront() << endl;
        }
        if (a == 'o') {
            mq.minpop();
        }
        
        v = mq.getArr();
        cout << "Array: ";
        for (auto p : v)
            cout << p.first << ":" << p.second << ", ";
        cout << endl;
    }

    return 0;
}
