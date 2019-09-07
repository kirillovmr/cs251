/*myvector.h*/

//
// Viktor Kirillov
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #01: myvector class that mimics std::vector, but with my own
// implemenation outlined as follows:
//
// [Node]  ->  [Node] -> nullptr
//  |             |
//  -> [Array]    -> [Array]

// Test 20 - erase all elements and then build up a new vector: test failed (myvector incorrect).

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
    
    Node *head, *tail, *prevNode = nullptr;
    int Size, Capacity, prevNodeIndex = -1;
    
public:
    // default constructor:
    myvector() {
        head = new Node; tail = head;
        head->A = new T[4];
        
        Size = 0; Capacity = 4;
    }
    
    // constructor with initial size:
    myvector(int initial_size) {
        head = new Node; tail = head;
        head->A = new T[initial_size];
        
        Size = initial_size; Capacity = initial_size;
    }
    
    // copy constructor for parameter passing:
    myvector (const myvector& other) {
        head = new Node; tail = head;
        head->A = new T[other.Capacity];
        
        Size = 0; Capacity = other.Capacity;
        
        Node *otherNode = other.head;
        while(otherNode != nullptr) {
            for (int i=0; i<other.Capacity; i++)
                if (size() < other.Size)
                    push_back( otherNode->A[i] );
            otherNode = otherNode->pNext;
        }
    }
    
    void displayAll() {
        Node *current = head;
        
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
    
    size_t size() {
        return Size;
    }
    
    // returns a reference to the element at position i
    T& operator[](int i) {
        return at(i);
    }
    
    T& at(int i) {
        // Getting responsible node index
        int nodeIndex = i / Capacity;
        int elementIndex = i % Capacity;
        
        if (prevNodeIndex > nodeIndex || prevNodeIndex <= 0) {
            prevNodeIndex = 0;
            prevNode = head;
        }
        
        // Going to appropriate node
        while (prevNodeIndex < nodeIndex) {
            prevNode = prevNode->pNext;
            prevNodeIndex++;
        }
        
        return *(prevNode->A+elementIndex);
    }
    
    void push_back(T value) {
        int elementIndex = Size % Capacity;
        
        // Creating next node if needed
        if (elementIndex == 0 && Size > 0)  {
//            cout << "Z\n";
            tail->pNext = new Node;
            tail->pNext->A = new T[Capacity];
            tail = tail->pNext;
        }
//        cout << "index " << elementIndex << endl;
        
        tail->A[elementIndex] = value;
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
        Node *currentNode = head;
        
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
        Node *currentNode = head, *previousNode;
        
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
            tail = previousNode;
            cout << "P\n";
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
                    tail = currentNode;
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
