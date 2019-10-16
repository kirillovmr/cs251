//
//  Rebalancing Tests.cpp
//  AVL Trees Tests
//
//  Created by Viktor Kirillov on 10/15/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "catch.hpp"
#include "avl.hpp"

using namespace std;

TEST_CASE("(1) AVL tree with 4 nodes")
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 4 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);
  avl.insert(125, -125);

  //
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 4);
  REQUIRE(avl.height() == 2);

  REQUIRE(keys[0] == 50);
  REQUIRE(values[0] == -50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(values[1] == -100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(values[2] == -125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(values[3] == -150);
  REQUIRE(heights[3] == 1);
}

TEST_CASE("(2) empty tree")
{
  avltree<int, int>  avl;

  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
}

TEST_CASE("(3) just one node")
{
  avltree<int, int>  avl;
    
    avl.insert(123, 88);

  REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);
    
    vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

    REQUIRE(keys[0] == 123);
    REQUIRE(values[0] == 88);
  REQUIRE(heights[0] == 0);
}



TEST_CASE("(3) Test root rebalancing")
{
    // Root Left Rotate small trees
    avltree<int, int>  avl1;
    
    avl1.insert(100, 3);
    avl1.insert(150, 3);
    avl1.insert(200, 3);
    
    vector<int>  keys, values, heights;

    keys = avl1.inorder_keys();
    heights = avl1.inorder_heights();
    
    REQUIRE(keys[0] == 100);
    REQUIRE(keys[1] == 150);
    REQUIRE(keys[2] == 200);
    
    REQUIRE(heights[0] == 0);
    REQUIRE(heights[1] == 1);
    REQUIRE(heights[2] == 0);
    
    
    // Root Right Rotate small trees
    avltree<int, int>  avl2;
    avl2.insert(100, 3);
    avl2.insert(90, 3);
    avl2.insert(80, 3);
    
    keys = avl2.inorder_keys();
    heights = avl2.inorder_heights();
    
    REQUIRE(keys[0] == 80);
    REQUIRE(keys[1] == 90);
    REQUIRE(keys[2] == 100);
    
    REQUIRE(heights[0] == 0);
    REQUIRE(heights[1] == 1);
    REQUIRE(heights[2] == 0);

    
    // Root double rotate 1
    avltree<int, int>  avl3;
    avl3.insert(100, 3);
    avl3.insert(150, 3);
    avl3.insert(90, 3);
    avl3.insert(80, 3);
    avl3.insert(95, 3);
    avl3.insert(96, 3);
    
    keys = avl3.inorder_keys();
    heights = avl3.inorder_heights();
    
    REQUIRE(keys[0] == 80);
    REQUIRE(keys[3] == 96);
    REQUIRE(keys[4] == 100);
    
    REQUIRE(heights[0] == 0);
    REQUIRE(heights[2] == 2);
    REQUIRE(heights[5] == 0);
        
    
     // Root double rotate 2
    avltree<int, int>  avl4;
    avl4.insert(100, 3);
    avl4.insert(50, 3);
    avl4.insert(150, 3);
    avl4.insert(125, 3);
    avl4.insert(175, 3);
    avl4.insert(110, 3);
    
    keys = avl4.inorder_keys();
    heights = avl4.inorder_heights();
    
    REQUIRE(keys[3] == 125);
    REQUIRE(keys[4] == 150);
    REQUIRE(keys[5] == 175);
    
    REQUIRE(heights[0] == 0);
    REQUIRE(heights[1] == 1);
    REQUIRE(heights[4] == 1);
    
    
    // Root single left rotate larger trees
    avltree<int, int>  avl5;
    avl5.insert(100, 3);
    avl5.insert(70, 3);
    avl5.insert(150, 3);
    avl5.insert(120, 3);
    avl5.insert(175, 3);
    avl5.insert(200, 3);
    
    keys = avl5.inorder_keys();
    heights = avl5.inorder_heights();
    
    REQUIRE(keys[0] == 70);
    REQUIRE(keys[3] == 150);
    REQUIRE(keys[5] == 200);
    
    REQUIRE(heights[1] == 1);
    REQUIRE(heights[2] == 0);
    REQUIRE(heights[4] == 1);
    
    
    // Root single right rotate larger trees
    avltree<int, int>  avl6;
    avl6.insert(100, 3);
    avl6.insert(150, 3);
    avl6.insert(50, 3);
    avl6.insert(25, 3);
    avl6.insert(75, 3);
    avl6.insert(21, 3);
    
    keys = avl6.inorder_keys();
    heights = avl6.inorder_heights();
    
    REQUIRE(keys[1] == 25);
    REQUIRE(keys[3] == 75);
    REQUIRE(keys[4] == 100);
    
    REQUIRE(heights[2] == 2);
    REQUIRE(heights[3] == 0);
    REQUIRE(heights[4] == 1);
}


TEST_CASE("(4) sub trees rebalancing")
{
    // single left rotated
    avltree<int, int>  avl1;
    avl1.insert(100, 3);
    avl1.insert(150, 3);
    avl1.insert(50, 3);
    avl1.insert(125, 3);
    avl1.insert(200, 3);
    avl1.insert(25, 3);
    avl1.insert(75, 3);
    avl1.insert(250, 3);
    avl1.insert(20, 3);
    avl1.insert(10, 3);
    
    vector<int>  keys, values, heights;
    keys = avl1.inorder_keys();
    heights = avl1.inorder_heights();
    
    REQUIRE(keys[1] == 20);
    REQUIRE(keys[3] == 50);
    REQUIRE(keys[4] == 75);
    REQUIRE(keys[5] == 100);
    REQUIRE(keys[7] == 150);
    REQUIRE(keys[9] == 250);
    
    REQUIRE(heights[2] == 0);
    REQUIRE(heights[3] == 2);
    REQUIRE(heights[4] == 0);
    REQUIRE(heights[6] == 0);
    REQUIRE(heights[7] == 2);
    REQUIRE(heights[8] == 1);
  
    // single right rotate
    avltree<int, int>  avl2;
    avl2.insert(100, 3);
    avl2.insert(200, 3);
    avl2.insert(50, 3);
    avl2.insert(250, 3);
    avl2.insert(54, 3);
    avl2.insert(60, 3);
    avl2.insert(150, 3);
    avl2.insert(175, 3);
    avl2.insert(70, 3);
    
    keys = avl2.inorder_keys();
    heights = avl2.inorder_heights();
    
    REQUIRE(keys[1] == 54);
    REQUIRE(keys[3] == 70);
    REQUIRE(keys[4] == 100);
    REQUIRE(keys[5] == 150);
    REQUIRE(keys[7] == 200);
    
    REQUIRE(heights[2] == 1);
    REQUIRE(heights[3] == 0);
    REQUIRE(heights[4] == 3);
    REQUIRE(heights[6] == 0);
    REQUIRE(heights[7] == 2);
    
    
     // double rotate 1
    avltree<int, int>  avl3;
    avl3.insert(55, 3);
    avl3.insert(48, 3);
    avl3.insert(64, 3);
    avl3.insert(60, 3);
    avl3.insert(78, 3);
    avl3.insert(38, 3);
    avl3.insert(51, 3);
    avl3.insert(16, 3);
    avl3.insert(40, 3);
    avl3.insert(45, 3);
    
    keys = avl3.inorder_keys();
    heights = avl3.inorder_heights();
    
    REQUIRE(keys[1] == 38);
    REQUIRE(keys[3] == 45);
    REQUIRE(keys[4] == 48);
    REQUIRE(keys[5] == 51);
    REQUIRE(keys[7] == 60);
    
    REQUIRE(heights[2] == 2);
    REQUIRE(heights[3] == 0);
    REQUIRE(heights[4] == 1);
    REQUIRE(heights[6] == 3);
    REQUIRE(heights[7] == 0);
    
     // double rotate 2
    avltree<int, int>  avl4;
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
     
    keys = avl4.inorder_keys();
    heights = avl4.inorder_heights();
    
    REQUIRE(keys[1] == 48);
    REQUIRE(keys[3] == 55);
    REQUIRE(keys[4] == 60);
    REQUIRE(keys[5] == 64);
    REQUIRE(keys[7] == 77);
    
    REQUIRE(heights[2] == 0);
    REQUIRE(heights[3] == 3);
    REQUIRE(heights[4] == 0);
    REQUIRE(heights[6] == 0);
    REQUIRE(heights[7] == 2);
}
    
    
    
    
