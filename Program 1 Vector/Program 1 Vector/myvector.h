/*myvector.h*/

//
// Viktor Kirillov
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #01: myvector class that mimics std::vector, but with my own
// implemenation outlined as follows:
//
// ???
//

#pragma once

#include <iostream>  // print debugging
#include <cstdlib>   // malloc, free

using namespace std;

template <class T>
class myvector
{
private:
    struct Node {
        T* A;
        Node *pNext = nullptr;
    };
    
    Node node;
    int Size;
    int Capacity;
    
public:
    // default constructor:
    myvector()
    {
        node.A = new T[4];
        Size = 0;
        Capacity = 4;
    }
    
    // constructor with initial size:
    myvector(int initial_size)
    {
        node.A = new T[initial_size];
        Size = initial_size;
        Capacity = initial_size;
    }
    
    // copy constructor for parameter passing:
    myvector(const myvector& other)
    {
        Size = 0;
        Capacity = other.Capacity;

        Node *prevNode = nullptr;
        Node *thisNode = &node;
        Node const *otherNode = &other.node;

        // Going through nodes
        while(otherNode != nullptr) {

            // Creating node if needed
            if (thisNode == nullptr) {
                thisNode = new Node;
                prevNode->pNext = thisNode;
            }

            // Initializing new array
            thisNode->A = new T[Capacity];

            for (int i=0; i<other.Capacity; i++) {
                if (Size < other.Size) {
                    thisNode->A[i] = otherNode->A[i];
                    Size++;
                }
            }

            prevNode = thisNode;
            thisNode = thisNode->pNext;
            otherNode = otherNode->pNext;
        }
    }
    
    void displayAll() {
        Node *current = &node;
        
        int j = 0;
        while(current) {
            for (int i=0; i<Capacity; i++) {
                if (j*Capacity + i < Size)
                    cout << current->A[i] << " ";
            }
            cout << endl;
            
            current = current->pNext;
            j++;
        }
    }
    
    int size()
    {
        return Size;
    }
    
    T& at(int i)
    {
        // Getting responsible node index
        int nodeIndex = i / Capacity;
        int elementIndex = i % Capacity;
        Node *currentNode = &node;
        
        // Going to appropriate node
        while (nodeIndex > 0) {
            currentNode = currentNode->pNext;
            nodeIndex--;
        }
        
        return *(currentNode->A+elementIndex);
    }
    
    void push_back(T value)
    {
        // Getting responsible node index
        int nodeIndex = Size / Capacity;
        int elementIndex = Size % Capacity;
        Node *currentNode = &node;
        
        // Going to appropriate node
        while (nodeIndex > 0) {
            
            // Creating next node if needed
            if (currentNode->pNext == nullptr) {
                currentNode->pNext = new Node;
                currentNode->pNext->A = new T[Capacity];
            }
            
            currentNode = currentNode->pNext;
            nodeIndex--;
        }
        
        currentNode->A[elementIndex] = value;
        Size++;
    }
};
