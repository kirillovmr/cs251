//
// Min queue that stores (key, value) pairs using a min-heap
// implementation.  When pop is called, the key from the
// (key, value) pair with the smallest value is returned; if
// two pairs have the same value, the smaller key is returned.
// Push and pop have O(lgN) time complexity.
//
// << YOUR NAME >>
//
// Original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #07
//

#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename TKey, typename TValue>
class minqueue {
private:
    vector<pair<TKey, TValue>> arr;
    map<TKey, int> m_map;
    
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return 2*i+1; }
    int right(int i) { return 2*i+2; }
    
    void heapUp(int i) {
        if (i > 0) {
            if (arr[i].second < arr[parent(i)].second) {
                swap(i, parent(i));
                heapUp(parent(i));
            }
            else if (arr[i].second == arr[parent(i)].second && arr[i].first < arr[parent(i)].first) {
                swap(i, parent(i));
                heapUp(parent(i));
            }
        }
    }
    
    void heapDown(int i) {
        // Searching for smallest value
        int smallest = i, l = left(i), r = right(i);
        if (l < arr.size()) {
            if (arr[l].second < arr[i].second)
                smallest = l;
            if (arr[l].second == arr[i].second && arr[l].first == arr[i].first)
                smallest = l;
        }
        
        if (r < arr.size()) {
            if (arr[r].second < arr[smallest].second)
                smallest = r;
            if (arr[r].second == arr[smallest].second && arr[r].first < arr[smallest].first)
                smallest = r;
        }
        
        if (smallest != i) {
            swap(i, smallest);
            heapDown(smallest);
        }
    }
    
    void swap(int a, int b) {
        pair<TKey, TValue> tmp(arr[a]);
        arr[a] = arr[b];
        arr[b] = tmp;
        
        // swap indeces in map
        m_map[arr[a].first] = m_map[arr[a].first] ^ m_map[arr[b].first];
        m_map[arr[b].first] = m_map[arr[a].first] ^ m_map[arr[b].first];
        m_map[arr[a].first] = m_map[arr[a].first] ^ m_map[arr[b].first];
    }
    
public:
    
    vector<pair<TKey, TValue>> getArr() {
        return arr;
    }
    //
    // default constructor:
    //
    // Queue has a max capacity for efficient implementation.
    // This max capacity must be specified at queue creation.
    //
    minqueue(int capacity) {
        arr.reserve(capacity);
    }
    
    //
    // fill constructor:
    //
    // This allows for the efficient O(N) construction of
    // a queue with an initial set of keys, all with the same
    // initial value.  The max capacity of the queue is
    // set to the # of keys provided for initialization;
    // it is assumed the keys are in ascending order.
    //
    minqueue(vector<TKey> keys, TValue initialValue) {
        arr.reserve(keys.size());
        for (TKey key: keys)
            pushinorder(key, initialValue);
    }
    
    //
    // empty:
    //
    // Returns true if empty, false if not.
    //
    bool empty() {
        return arr.size() == 0;
    }
    
    //
    // push:
    //
    // Inserts the given (key, value) pair into the queue such that
    // pop always returns the pair with the minimum value.  If the
    // key is *already* in the queue, it's value is updated to the
    // given value and the queue reordered.  If the key is not in
    // the queue, the (key, value) pairs is added and the queue
    // reordered.
    //
    // NOTE: if two keys have the same value, i.e. (key1, value) and
    // (key2, value), then those pairs are ordered into ascending value
    // by their key.
    //
    void pushinorder(TKey key, TValue value) {

        // We need to insert a new (key, value) pair but the queue is full:
        if (arr.size() == arr.capacity())
          throw runtime_error("minqueue::pushinorder: queue full");
        
        auto it = m_map.find(key);
        // If key is not in the list
        if (it == m_map.end()) {
            arr.push_back(pair<TKey, TValue>(key, value));
            m_map[key] = static_cast<int>(arr.size())-1;
            heapUp(static_cast<int>(arr.size())-1);
        }
        // If key is in the list
        else {
            int idx = it->second;
            arr[idx].second = value;
            heapUp(idx);
            heapDown(idx);
        }
    }
    
    
    //
    // front:
    //
    // Returns the key at the front of the queue; does *not* pop the
    // (key, value) pair.  Throws a logic_error exception if the queue
    // is empty.
    //
    TKey minfront() {
        if (empty())
            throw logic_error("minqueue::minfront: queue empty");
        return arr[0].first;
    }
    
    
    //
    // pop:
    //
    // Pops and discards the (key, value) pair at the front of the queue.
    // Throws a logic_error exception if the queue is empty.
    //
    void minpop() {
        if (empty())
            throw logic_error("minqueue::minpop: queue empty");
        
        swap(0, static_cast<int>(arr.size())-1);
        m_map.erase(arr[arr.size()-1].first);
        arr.pop_back();
        
        heapDown(0);
    }
    
};
