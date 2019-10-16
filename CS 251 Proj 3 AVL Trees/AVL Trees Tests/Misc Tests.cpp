//
//  Misc Tests.cpp
//  AVL Trees Tests
//
//  Created by Viktor Kirillov on 10/16/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "catch.hpp"
#include "avl.hpp"

using namespace std;

TEST_CASE("MISC (1) Clear tree") {
    avltree<int, int> tree;
    tree.insert(100, 150);
    tree.insert(150, 200);
    tree.insert(200, 250);
    
    SECTION("Just clear") {
        tree.clear();
        REQUIRE(tree.height() == -1);
        REQUIRE(tree.size() == 0);
    }
    
    SECTION("Clear then insert") {
        tree.clear();
        tree.insert(100, 500);
        tree.insert(200, 500);
        tree.insert(300, 500);
        
        REQUIRE(tree.height() == 1);
        REQUIRE(tree.size() == 3);
    }
    
    SECTION("Copy constructor, then clear") {
        avltree<int, int> tree2;
        tree2 = tree;
        
        tree2.clear();
        
        REQUIRE(tree.height() == 1);
        REQUIRE(tree.size() == 3);
        
        REQUIRE(tree2.height() == -1);
        REQUIRE(tree2.size() == 0);
    }
}

TEST_CASE("MISC (2) Distance no balance") {
    avltree<int, int> t;
    t.setSelfBalance(false);
    
    t.insert(46, -100);
    t.insert(29, -150);
    t.insert(76, -120);
    t.insert(17, -100);
    t.insert(31, -150);
    t.insert(100, -120);
    t.insert(12, -100);
    t.insert(20, -150);
    t.insert(5, -120);
    
    REQUIRE(t.distance(46, 12) == 3);
    REQUIRE(t.distance(12, 46) == 3);
    REQUIRE(t.distance(5, 100) == 6);
    REQUIRE(t.distance(100, 5) == 6);
    REQUIRE(t.distance(31, 12) == 3);
    REQUIRE(t.distance(12, 31) == 3);
    
    REQUIRE(t.distance(12, 12) == 0);
    REQUIRE(t.distance(29, 200000) == -1);
}

TEST_CASE("MISC (3) Distance balance") {
    avltree<int, int> avl4;
    
    avl4.insert(55, 3);
    avl4.insert(48, 3);
    avl4.insert(64, 3);
    avl4.insert(60, 3);
    avl4.insert(78, 3);
    avl4.insert(38, 3);
    avl4.insert(51, 3);
    avl4.insert(85, 3);
    avl4.insert(77, 3);
    avl4.insert(76, 3);
    
    REQUIRE(avl4.distance(38, 85) == 5);
    REQUIRE(avl4.distance(51, 38) == 2);
    REQUIRE(avl4.distance(64, 85) == 3);
    REQUIRE(avl4.distance(85, 85) == 0);
    REQUIRE(avl4.distance(55, 60) == 3);
    REQUIRE(avl4.distance(60, 55) == 3);
}
