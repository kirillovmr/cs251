//
//  avl.hpp
//  CS 251 Proj 3 AVL Trees
//
//  Created by Viktor Kirillov on 10/15/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#pragma once

#include <algorithm>  // std::max
#include <iostream>
#include <vector>
#include <memory>
#include <stack>

template<typename TKey, typename TValue>
class avltree {
private:
    struct Node {
        TKey Key;
        TValue Value;
        int Height;
        std::shared_ptr<Node> Left = nullptr;
        std::shared_ptr<Node> Right = nullptr;
    };
    
    std::shared_ptr<Node> Root;
    int Size;
    
    void _copyHelper(std::shared_ptr<Node> our, std::shared_ptr<Node> other) {
        if (other->Left) {
            our->Left = std::shared_ptr<Node>(new Node{other->Left->Key, other->Left->Value, other->Left->Height});
            _copyHelper(our->Left, other->Left);
        }
        if (other->Right) {
            our->Right = std::shared_ptr<Node>(new Node{other->Right->Key, other->Right->Value, other->Right->Height});
            _copyHelper(our->Right, other->Right);
        }
    }
    
    void _inorder(std::shared_ptr<Node> cur) {
        if (cur->Left) { _inorder(cur->Left); }
        std::cout << cur->Key << " ";
        if (cur->Right) { _inorder(cur->Right); }
    }
    
    void _inorderKeys(std::shared_ptr<Node> cur, std::vector<TKey> &keys) {
        if (cur->Left) { _inorderKeys(cur->Left, keys); }
        keys.push_back(cur->Key);
        if (cur->Right) { _inorderKeys(cur->Right, keys); }
    }
    
    void _inorderValues(std::shared_ptr<Node> cur, std::vector<TValue> &values) {
        if (cur->Left) { _inorderValues(cur->Left, values); }
        values.push_back(cur->Value);
        if (cur->Right) { _inorderValues(cur->Right, values); }
    }
    
    void _inorderHeights(std::shared_ptr<Node> cur, std::vector<int> &heights) {
        if (cur->Left) { _inorderHeights(cur->Left, heights); }
        heights.push_back(cur->Height);
        if (cur->Right) { _inorderHeights(cur->Right, heights); }
    }
    
    // Rotates the tree around the node N, where Parent is N's parent.
    void _RightRotate(std::shared_ptr<Node> Parent, std::shared_ptr<Node> N) {
        // assert(N != nullptr);  // pre-conditions: N and L must exist
        // assert(N->Left != nullptr);

        std::shared_ptr<Node> x = N->Left;
        std::shared_ptr<Node> Temp = x->Right;

        if (Parent == nullptr)
            Root = x;
        else if (Parent->Left) {
            if (Parent->Left->Key == N->Key)
               Parent->Left = x;
            else
               Parent->Right = x;
        }
        else
            Parent->Right = x;

        // Rotation
        x->Right = N;
        N->Left = Temp;

        // Heights
        N->Height = std::max(_height(N->Left), _height(N->Right)) + 1;
        x->Height = std::max(_height(x->Left), _height(N->Right)) + 1;
    }
    
    // Rotates the tree around the node N, where Parent is N's parent.
    void _LeftRotate(std::shared_ptr<Node> Parent, std::shared_ptr<Node> N) {
        // assert(N != nullptr);  // pre-conditions: N and R must exist
        // assert(N->Right != nullptr);

        std::shared_ptr<Node> x = N->Right;
        std::shared_ptr<Node> Temp = x->Left;

        if (Parent == nullptr)
            Root = x;
        else if (Parent->Left) {
            if (Parent->Left->Key == N->Key)
               Parent->Left = x;
            else
               Parent->Right = x;
        }
        else
            Parent->Right = x;

        // Rotation
        x->Left = N;
        N->Right = Temp;

        // Heights
        N->Height = std::max(_height(N->Left), _height(N->Right)) + 1;
        x->Height = std::max(_height(x->Left), _height(N->Right)) + 1;
     
    }
    
    int _height(std::shared_ptr<Node> t) {
        return (t == nullptr ? -1 : t->Height);
    }
    
public:
    avltree() : Size(0), Root(nullptr) { }
    
    avltree(avltree &other) : Size(other.Size), Root(nullptr) {
        if (other.Root != nullptr) {
            Root = new Node{other.Root->Key, other.Root->Value, other.Root->Height};
            _copyHelper(Root, other.Root);
        }
    }
    
    int size() {
        return Size;
    }
    
    int height() {
        return Root ? Root->Height : -1;
    }
    
    void clear() {
        //   Because of smart pointers  //
         //      Thats all we need     //
          //   ❤️ smart pointers ❤️   //
        Root = nullptr;
    }
    
    TValue* search(TKey key) {
        std::shared_ptr<Node> cur = Root;
        
        while (cur != nullptr)
            if (key == cur->Key)
                return &(cur->Value);
            else if (key < cur->Key)
                cur = cur->Left;
            else
                cur = cur->Right;
    
        // if get here, not found
        return nullptr;
    }
    
    void insert(TKey key, TValue value) {
        std::shared_ptr<Node> prev = nullptr;
        std::shared_ptr<Node> cur = Root;

        // stack the nodes we visit so we can walk back up
        // the search path later, adjusting heights:
        std::stack< std::shared_ptr<Node> > nodes;

        // 1. Search to see if tree already contains key:
        while (cur != nullptr) {
            if (key == cur->Key)  // already in tree
                return;

            nodes.push(cur);  // stack so we can return later:

            if (key < cur->Key) {
                prev = cur;
                cur = cur->Left;
            }
            else {
                prev = cur;
                cur = cur->Right;
            }
        }

        // 2. if we get here, key is not in tree, so allocate a new node to insert:
        std::shared_ptr<Node> newNode = std::shared_ptr<Node>(new Node{key, value, 0});

        // 3. link in the new node:
        if (prev == nullptr)
            Root = newNode;
        else if (key < prev->Key)
            prev->Left = newNode;
        else
            prev->Right = newNode;

        // 4. update size:
        Size++;

        // 5. walk back up tree using stack and update heights:
        while (nodes.size()) {
            cur = nodes.top();
            nodes.pop();

            int HL = cur->Left ? cur->Left->Height : -1;
            int HR = cur->Right ? cur->Right->Height : -1;
            int newH = 1 + std::max(HL, HR);
            cur->Height = newH;
            
            if (true) {
                // Get balance factor
                int balance = HL - HR;
                std::shared_ptr<Node> top = nodes.size() ? nodes.top() : nullptr;
                
                // Left Left Case
                if (balance > 1 && key < cur->Left->Key) {
//                    std::cout << "LL\n";
                    _RightRotate(top, cur);
                }
                
                // Right Right Case
                else if (balance < -1 && key > cur->Right->Key) {
//                    std::cout << "RR\n";
                    _LeftRotate(top, cur);
                }
                
                // Left Right Case
                else if (balance > 1 && key > cur->Left->Key) {
//                    std::cout << "LR\n";
                    _LeftRotate(cur, cur->Left);
                    _RightRotate(top, cur);
                }
                
                // Right Left Case
                else if (balance < -1 && key < cur->Right->Key) {
//                    std::cout << "RL\n";
                    _RightRotate(cur, cur->Right);
                    _LeftRotate(top, cur);
                }
            }
        }
    }
    
    int distance(TKey k1, TKey k2) {
        
    }
    
    void inorder() {
       std::cout << "Inorder: ";
       _inorder(Root);
       std::cout << std::endl;
    }
    
    std::vector<TKey> inorder_keys() {
        std::vector<TKey> keys;
        _inorderKeys(Root, keys);
        return keys;
    }
    
    std::vector<TValue> inorder_values() {
        std::vector<TValue> values;
        _inorderValues(Root, values);
        return values;
    }
    
    std::vector<int> inorder_heights() {
        std::vector<int> heights;
        _inorderHeights(Root, heights);
        return heights;
    }
};
