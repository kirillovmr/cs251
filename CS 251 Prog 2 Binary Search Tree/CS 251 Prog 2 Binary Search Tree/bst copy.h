//
//  Binary search tree
//  CS 251 Prog 2 Binary Search Tree
//
//  Created by Viktor Kirillov on 9/19/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef bts_hpp
#define bts_hpp

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree {
private:
    struct NODE {
        TKey    Key;
		TValue	Value;
        NODE*   Left = nullptr;
        NODE*   Right = nullptr;
    };
    
    NODE* Root;  // pointer to root node of tree (nullptr if empty)
    int   Size;  // # of nodes in the tree (0 if empty)
    
    // _inorder does the actual inorder traversal and output
    // to console.  Each key is output to the console followed
    // by " ", including the last key.
    void _inorder(NODE* cur) {
        if (cur == nullptr)
            return;
        else {
            _inorder(cur->Left);
            // cout << cur->Key << " ";
            cout << cur->Key << ":" << cur->Value.PubYear << " ";
            _inorder(cur->Right);
        }
    }
    
    void _copyHelper(NODE *our, NODE *other) {
        if (other->Left) {
            NODE* node = new NODE{other->Left->Key, other->Left->Value};
            our->Left = node;
            Size++;
            _copyHelper(our->Left, other->Left);
        }
        if (other->Right) {
            NODE* node = new NODE{other->Right->Key, other->Right->Value};
            our->Right = node;
            Size++;
            _copyHelper(our->Right, other->Right);
        }
    }
    
    int _height(NODE *node) {
        if (node == nullptr)
            return 0;
        
        int left = _height(node->Left);
        int right = _height(node->Right);
        
        return left > right ? left+1 : right+1;
    }
    
public:
    // Default constructor:
    binarysearchtree() {
        Root = nullptr;
        Size = 0;
    }
    
    // Copy constructor
    // I'm not using bbuilt-in functions like insert() coz its less efficient then my approach
    binarysearchtree(binarysearchtree& other) {
        if (other.Root == nullptr) {
            Root = nullptr;
            Size = 0;
        } else {
            NODE *node = new NODE{other.Root->Key, other.Root->Value};
            Root = node;
            Size = 1;
            _copyHelper(Root, other.Root);
        }
    }
    
    // Returns the # of nodes in the tree, 0 if empty.
    int size() {
        return Size;
    }
    
    // Computes and returns height of tree; height of an empty tree is
    // defined as -1.
    int height() {
        if (Root == nullptr)
            return -1;
        
        int left = _height(Root->Left);
        int right = _height(Root->Right);
        
        return left > right ? left : right;
    }
    
    // Searches the tree for the given key, returning true if found
    // and false if not.
    TValue* search(TKey key) {
        NODE* cur = Root;
        
        while (cur != nullptr) {
            if (key == cur->Key)  // already in tree
                return &(cur->Value);
            if (key < cur->Key) // search left:
                cur = cur->Left;
            else
                cur = cur->Right;
        }
        
        // if get here, not found
        return nullptr;
    }
    
    // Inserts the given key into the tree; if the key has already been insert then
    // the function returns without changing the tree.
    void insert(TKey key, TValue value) {
        NODE* prev = nullptr;
        NODE* cur = Root;
        
        // 1. Search to see if tree already contains key:
        while (cur != nullptr) {
            if (key == cur->Key)  // already in tree
                return;
            
            if (key < cur->Key) { // search left:
                prev = cur;
                cur = cur->Left;
            }
            else {
                prev = cur;
                cur = cur->Right;
            }
        }
        
        // 2. if we get here, key is not in tree, so allocate a new node to insert:
        NODE *newNode = new NODE{key, value};
        
        // 3. link in the new node:
        if (Root == nullptr)
            Root = newNode;
        else {
            cur = Root;
            while(cur) {
                if (key < cur->Key) {
                    if (cur->Left)
                        cur = cur->Left;
                    else {
                        cur->Left = newNode;
                        break;
                    }
                }
                else {
                    if (key > cur->Key) {
                        if (cur->Right)
                            cur = cur->Right;
                        else {
                            cur->Right = newNode;
                            break;
                        }
                    }
                }
            }
        }

        // 4. update size and we're done:
        Size += 1;

    }
    
    // Performs an inorder traversal of the tree, outputting
    // the keys to the console.
    void inorder() {
        cout << "Inorder: ";
        _inorder(Root);
        cout << endl;
    }
};

#endif /* bts_hpp */
