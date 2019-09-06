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
class myvector {
private:
    struct Node {
        T* A;
        Node *pNext = nullptr;
    };
    
    Node *node;
    int Size;
    int Capacity;
    
public:
    // default constructor:
    myvector() {
        node = new Node;
        node->A = new T[4];
        Size = 0;
        Capacity = 4;
    }
    
    // constructor with initial size:
    myvector(int initial_size) {
        node = new Node;
        node->A = new T[initial_size];
        Size = initial_size;
        Capacity = initial_size;
    }
    
    // copy constructor for parameter passing:
    myvector(const myvector& other) {
        
        Node *prevNode = nullptr, *thisNode = node;
        Node const *otherNode = other.node;
        
        // Clearing vector if it is not empty
        if (Size) {
            while (thisNode) {
                if (prevNode)
                    deleteNode(prevNode);
                
                prevNode = thisNode;
                thisNode = thisNode->pNext;
            }
        }
        
        Size = 0;
        Capacity = other.Capacity;
        node = new Node;
        thisNode = node;

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
    
    // returns a reference to the element at position i
    T& operator[](int i) {
        return at(i);
    }
    
    void displayAll() {
        Node *current = node;
        
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
    
    int size() {
        return Size;
    }
    
    T& at(int i) {
        // Getting responsible node index
        int nodeIndex = i / Capacity;
        int elementIndex = i % Capacity;
        Node *currentNode = node;
        
        // Going to appropriate node
        while (nodeIndex > 0) {
            currentNode = currentNode->pNext;
            nodeIndex--;
        }
        
        return *(currentNode->A+elementIndex);
    }
    
    void push_back(T value) {
        // Getting responsible node index
        int nodeIndex = Size / Capacity;
        int elementIndex = Size % Capacity;
        Node *currentNode = node;
        
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
    
    // Returns the elements in the range of positions i..j, inclusive.
    T* rangeof(int i, int j) {
        int size = j - i + 1;
        
        if (size < 1)
            return nullptr;
        
        // Allocating array to be returned
        T* arr = new T[size];
        
        int nodeIndex = i / Capacity;
        int elementIndex = i % Capacity;
        Node *currentNode = node;
        
        // Going to appropriate node
        while (nodeIndex > 0) {
            currentNode = currentNode->pNext;
            nodeIndex--;
        }
        
        int k = 0;
        while (k < size) {
            arr[k++] = currentNode->A[elementIndex++];
            
            // Moving to next node
            if (elementIndex == Capacity) {
                currentNode = currentNode->pNext;
                elementIndex = 0;
            }
        }
        
        return arr;
    }
    
    void deleteNode(Node *node) {
        delete[] node->A;
        delete node;
    }
    
    // erase the element at position i from the vector by overwriting it and
    // reducing the size (# of elements);
    T erase(int i) {
        
        int nodeIndex = i / Capacity;
        int elementIndex = i % Capacity;
        Node *currentNode = node, *previousNode;
        
        // Going to appropriate node
        while (nodeIndex > 0) {
            previousNode = currentNode;
            currentNode = currentNode->pNext;
            nodeIndex--;
        }
        T erasedElement = currentNode->A[elementIndex];
        
        // If erasing last element on index 0 in node
        if (i == Size - 1 && elementIndex == 0 && i/Capacity != 0) {
            deleteNode(currentNode);
            // Even that there is warning that wariable may be unitialized, it is initialized within this if statement
            previousNode->pNext = nullptr;
        }
        
        while (i+1 < Size) {
            // If next element in the same node
            if (elementIndex + 1 < Capacity) {
                currentNode->A[elementIndex] = currentNode->A[elementIndex + 1];
                elementIndex++;
            }
            // If next element in the next node
            else {
                currentNode->A[elementIndex] = currentNode->pNext->A[0];
                
                // If it was the last element to shift
                if (i == Size - 2) {
                    // Deleting next node if it had only 1 element
                    deleteNode(currentNode->pNext);
                    currentNode->pNext = nullptr;
                    break;
                }
                
                currentNode = currentNode->pNext;
                elementIndex = 0;
            }
            i++;
        }
        Size--;
        
        return erasedElement;
    }
};
