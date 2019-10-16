//
//  main.cpp
//  CS 251 Proj 3 AVL Trees
//
//  Created by Viktor Kirillov on 10/15/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "avl.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
    avltree<int, int> t;
    t.insert(100, -100);
    t.insert(150, -150);
    t.insert(120, -120);
    t.inorder();
    t.clear();
    
    return 0;
}

