//
//  BST Test.cpp
//  AVL Trees Tests
//
//  Created by Viktor Kirillov on 10/15/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <vector>

#include "catch.hpp"
#include "avl.hpp"

using namespace std;

TEST_CASE( "Test 01", "[Project02]" ) {
    avltree<int, int>  T;
    T.setSelfBalance(false);
            
    REQUIRE(T.size() == 0);
    REQUIRE(T.height() == -1);
}

TEST_CASE("Test 02", "[Project02]") {
    avltree<int, int>  T;
    avltree<int, int>  T2;
    T.setSelfBalance(false);
    T2.setSelfBalance(false);

    REQUIRE(T.size() == 0);
    REQUIRE(T.height() == -1);
    REQUIRE(T2.size() == 0);
    REQUIRE(T2.height() == -1);

    T.insert(10, 20);

    REQUIRE(T.size() == 1);
    REQUIRE(T.height() == 0);
    REQUIRE(T2.size() == 0);
    REQUIRE(T2.height() == -1);
}

TEST_CASE("Test 03", "[Project02]") {
    avltree<int, int>  T;
    avltree<int, int>  T2;
    T.setSelfBalance(false);
    T2.setSelfBalance(false);

    REQUIRE(T.size() == 0);
    REQUIRE(T.height() == -1);
    REQUIRE(T2.size() == 0);
    REQUIRE(T2.height() == -1);

    T.insert(10, 20);
    T.insert(20, 20);
    T.insert(15, 20);

    T2.insert(10, 20);
    T2.insert(5, 20);

    REQUIRE(T.size() == 3);
    REQUIRE(T.height() == 2);
    REQUIRE(T2.size() == 2);
    REQUIRE(T2.height() == 1);
}

TEST_CASE("Test 04", "[Project02]") {
    avltree<int, int>  T1;
    avltree<string, int>  T2;
    avltree<double, string>  T3;
    avltree<int, int>  T4;
    T1.setSelfBalance(false);
    T2.setSelfBalance(false);
    T3.setSelfBalance(false);
    T4.setSelfBalance(false);

    for (int i = 0; i < 25; ++i)
        T1.insert(i, -i);

    T4.insert(50, -50);
    T4.insert(-50, 50);
    for (int i = 0; i < 25; ++i)
        T4.insert(i, -i*100);


    T2.insert("mom", 555);
    T2.insert("pizza", 123);
    T2.insert("cat", 999);
    T2.insert("friend", 23456);
    T2.insert("dog", 12345);
    T2.insert("elephant", 6);

    REQUIRE(T1.size() == 25);
    REQUIRE(T1.height() == 24);

    REQUIRE(T4.size() == 27);
    REQUIRE(T4.height() == 26);

    REQUIRE(T2.size() == 6);
    REQUIRE(T2.height() == 4);

    REQUIRE(T3.size() == 0);
    REQUIRE(T3.height() == -1);

    T2.insert("friend", 23457);
    T2.insert("mom", 556);
    T2.insert("elephant", 7);
    T2.insert("cat", 1000);
    T2.insert("dog", 12347);
    T2.insert("pizza", 124);

    REQUIRE(T1.size() == 25);
    REQUIRE(T1.height() == 24);

    REQUIRE(T2.size() == 6);
    REQUIRE(T2.height() == 4);

    REQUIRE(T3.size() == 0);
    REQUIRE(T3.height() == -1);
}

TEST_CASE("Test 05", "[Project02]") {
    avltree<int, int> tree;
    tree.setSelfBalance(false);
    int N = 1000000;

    //std::random_device random_device;
    std::mt19937 random_engine(12345);
    std::uniform_int_distribution<int> distributionAgent(1, N * 10);

    while (tree.size() < N) {
        int ranInt = distributionAgent(random_engine);
        tree.insert(ranInt, ranInt);
    }

    REQUIRE(tree.size() == N);
    REQUIRE(tree.height() == 48);
}

TEST_CASE("Test 06", "[Project02]") {
    avltree<int, int>  T1;
    T1.setSelfBalance(false);

    T1.insert(12, 144);
    T1.insert(6, 36);
    T1.insert(18, 324);

    for (int i = 1; i <= 25; ++i)
        T1.insert(i, i*i);

    REQUIRE(T1.size() == 25);
    REQUIRE(T1.height() == 8);

    REQUIRE(T1.search(0) == nullptr);
    REQUIRE(T1.search(26) == nullptr);
    REQUIRE(T1.search(144) == nullptr);
    REQUIRE(T1.search(324) == nullptr);

    for (int i = 1; i <= 25; ++i)
    {
        int* ip = T1.search(i);

        REQUIRE(ip != nullptr);
        REQUIRE((*ip) == (i * i));
    }
}

TEST_CASE("Test 07", "[Project02]") {
    avltree<int, int>  T1;
    avltree<int, int>  T2;
    T1.setSelfBalance(false);
    T2.setSelfBalance(false);

    T1.insert(12, 144);
    T1.insert(6, 36);
    T1.insert(18, 324);

    for (int i = 1; i <= 25; ++i)
        T1.insert(i, i * i);

    T2.insert(12, 24);
    T2.insert(6, 12);
    T2.insert(18, 36);

    for (int i = 0; i <= 26; ++i)
        T2.insert(i, i+i);

    REQUIRE(T1.size() == 25);
    REQUIRE(T1.height() == 8);

    REQUIRE(T2.size() == 27);
    REQUIRE(T2.height() == 9);

    REQUIRE(T1.search(0) == nullptr);
    REQUIRE(T1.search(26) == nullptr);
    REQUIRE(T1.search(144) == nullptr);
    REQUIRE(T1.search(324) == nullptr);
 
    for (int i = 1; i <= 25; ++i) {
        int* ip = T1.search(i);

        REQUIRE(ip != nullptr);
        REQUIRE((*ip) == (i * i));
    }

    REQUIRE(T2.search(-1) == nullptr);
    REQUIRE(T2.search(27) == nullptr);
    REQUIRE(T2.search(52) == nullptr);

    for (int i = 26; i >= 0; --i) {
        int* ip = T2.search(i);

        REQUIRE(ip != nullptr);
        REQUIRE((*ip) == (i + i));
    }
}

TEST_CASE("Test 08", "[Project02]") {
    avltree<int, int>  T1;
    avltree<int, int>  T2;
    T1.setSelfBalance(false);
    T2.setSelfBalance(false);

    REQUIRE(T1.size() == 0);
    REQUIRE(T1.height() == -1);

    REQUIRE(T2.size() == 0);
    REQUIRE(T2.height() == -1);

    T1.insert(12, 144);
    T1.insert(6, 36);
    T1.insert(18, 324);

    for (int i = 1; i <= 25; ++i)
        T1.insert(i, i * i);

    T2.insert(12, 24);
    T2.insert(6, 12);
    T2.insert(18, 36);

    for (int i = 0; i <= 26; ++i)
        T2.insert(i, i + i);

    for (int i = 1; i <= 25; ++i) {
        int* ip = T1.search(i);

        REQUIRE(ip != nullptr);
        REQUIRE((*ip) == (i * i));

        *ip = 2 * i - 1;

        ip = T2.search(i);

        REQUIRE(ip != nullptr);
        REQUIRE((*ip) == (i + i));

        *ip = i * i + 1;
    }

    // in T2, i=0 and i=26 should remain unchanged:
    REQUIRE(((T2.search(0) != nullptr) && (*(T2.search(0)) == 0)));
    REQUIRE(((T2.search(26) != nullptr) && (*(T2.search(26)) == 52)));

    // make sure the changes occurred correctly, to the correct nodes:
    for (int i = 1; i <= 25; ++i) {
        int* ip = T1.search(i);

        REQUIRE(ip != nullptr);
        REQUIRE((*ip) == (2*i - 1));

        ip = T2.search(i);

        REQUIRE(ip != nullptr);
        REQUIRE((*ip) == (i*i + 1));
    }
}

TEST_CASE("Test 09", "[Project02]") {
    avltree<string, int>  tree1;
    tree1.setSelfBalance(false);
    avltree<string, int>  tree2 = tree1;  // copy constructor

    REQUIRE(tree1.size() == 0);
    REQUIRE(tree1.height() == -1);

    REQUIRE(tree2.size() == 0);
    REQUIRE(tree2.height() == -1);
}

TEST_CASE("Test 10", "[Project02]") {
  avltree<string, int>  tree1;
    tree1.setSelfBalance(false);
 
  tree1.insert("mom", 123);
  tree1.insert("dad", 999);
  tree1.insert("parents", 101);
  tree1.insert("oscar", 102);
  tree1.insert("zizza", -11);
 
  REQUIRE(tree1.size() == 5);
  REQUIRE(tree1.height() == 2);
 
  avltree<string, int>  tree2 = tree1;  // copy constructor
 
  // copy correct?
  REQUIRE(tree2.size() == 5);
  REQUIRE(tree2.height() == 2);
 
  REQUIRE(((tree2.search("mom") != nullptr) && (*(tree2.search("mom")) == 123)));
  REQUIRE(((tree2.search("dad") != nullptr) && (*(tree2.search("dad")) == 999)));
  REQUIRE(((tree2.search("parents") != nullptr) && (*(tree2.search("parents")) == 101)));
  REQUIRE(((tree2.search("oscar") != nullptr) && (*(tree2.search("oscar")) == 102)));
  REQUIRE(((tree2.search("zizza") != nullptr) && (*(tree2.search("zizza")) == -11)));
 
  // original tree correct?
  REQUIRE(tree1.size() == 5);
  REQUIRE(tree1.height() == 2);
 
  REQUIRE(((tree1.search("mom") != nullptr) && (*(tree1.search("mom")) == 123)));
  REQUIRE(((tree1.search("dad") != nullptr) && (*(tree1.search("dad")) == 999)));
  REQUIRE(((tree1.search("parents") != nullptr) && (*(tree1.search("parents")) == 101)));
  REQUIRE(((tree1.search("oscar") != nullptr) && (*(tree1.search("oscar")) == 102)));
  REQUIRE(((tree1.search("zizza") != nullptr) && (*(tree1.search("zizza")) == -11)));
}

TEST_CASE("Test 11", "[Project02]") {
  avltree<int, int>  T1;
    T1.setSelfBalance(false);
 
  T1.insert(12, 144);
  T1.insert(6, 36);
  T1.insert(18, 324);
 
  for (int i = 1; i <= 25; ++i)
    T1.insert(i, i * i);
 
  REQUIRE(T1.size() == 25);
  REQUIRE(T1.height() == 8);
 
  avltree<int, int>  T2 = T1;  // copy constructor
 
  REQUIRE(T2.size() == 25);
  REQUIRE(T2.height() == 8);
 
  for (int i = 1; i <= 25; ++i) {
    int* ip = T1.search(i);
 
    REQUIRE(ip != nullptr);
    REQUIRE((*ip) == (i * i));
 
    *ip = 2 * i - 1;  // change values in T1
 
    ip = T2.search(i);
 
    REQUIRE(ip != nullptr);
    REQUIRE((*ip) == (i * i));  // T2 unchanged?
 
    *ip = i + 1;
  }
 
  //
  // make sure changes were retained in each tree:
  //
  for (int i = 1; i <= 25; ++i) {
    int* ip = T1.search(i);
 
    REQUIRE(ip != nullptr);
    REQUIRE((*ip) == (2*i - 1));
 
    ip = T2.search(i);
 
    REQUIRE(ip != nullptr);
    REQUIRE((*ip) == (i+1));
  }
 
  REQUIRE(T1.search(0) == nullptr);
  REQUIRE(T1.search(26) == nullptr);
 
  REQUIRE(T2.search(0) == nullptr);
  REQUIRE(T2.search(26) == nullptr);
}

TEST_CASE("Test 12", "[Project02]") {
  avltree<int, int>  tree;
    tree.setSelfBalance(false);
  int N = 100000;
 
  //std::random_device random_device;
  std::mt19937 random_engine(12345);
  std::uniform_int_distribution<int> distributionAgent(1, N * 10);
 
  while (tree.size() < N) {
    int ranInt = distributionAgent(random_engine);
    tree.insert(ranInt, ranInt);
  }
 
  REQUIRE(tree.size() == N);
  REQUIRE(tree.height() == 41);
 
  avltree<int, int>  T2 = tree;  // copy constructor:
 
  REQUIRE(T2.size() == N);
  REQUIRE(T2.height() == 41);
}
