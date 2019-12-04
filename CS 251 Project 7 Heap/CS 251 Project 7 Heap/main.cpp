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
    
    minqueue<char, int> mq(20);
    mq.pushinorder('b', 1);
    mq.pushinorder('a', 1);
    mq.pushinorder('c', 1);
    mq.pushinorder('d', 1);
    mq.pushinorder('e', 1);
//    mq.minpop();
    
    vector<pair<char, int>> v = mq.getArr();
    for (auto p : v)
        cout << p.first << ":" << p.second << ", ";
    cout << endl;
    cout << mq.minfront() << endl;
    
    return 0;
}
