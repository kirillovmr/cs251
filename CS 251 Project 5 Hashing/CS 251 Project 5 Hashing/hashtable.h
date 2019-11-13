//
//  hashtable.h
//  CS 251 Project 5 Hashing
//
//  Implements a hashtable, providing Get and Set functions
//  for accessing the underlying array.
//
//  It is assumed that collisions are handled using probing.
//  To support this, each location contains an "Empty" flag
//  which is true if the array location is empty, and false
//  if the location is in use.  Each locadtion also contains
//  both the key and value, for resolving collisions.
//
//  Created by Viktor Kirillov on 11/11/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef hashtable_h
#define hashtable_h

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class ILplates;

template<typename TKey, typename TValue>
class hashtable {
private:
    friend class ILplates;
    struct KeyValuePair {
        bool   Empty;
        TKey   Key;
        TValue Value;

        KeyValuePair(): Empty(true), Key(), Value() {}
    };

    int N;
    KeyValuePair *Hashtable;  // array of (key, value) pairs

    int _Probes;
    int _Stores;

public:
    hashtable(int size): N(size), _Probes(0), _Stores(0) {
        Hashtable = new KeyValuePair[N];
    }

    virtual ~hashtable() {
        
        // count the # of elements in the hash table:
        int elements = 0;
        for (int i = 0; i < N; ++i)
            if (!Hashtable[i].Empty)
                elements++;

        // output stats:
        cout << "\n**Hashing Stats**" << endl
            << "Probes: " << _Probes << endl
            << "Stores: " << _Stores << endl
            << "Elements: " << elements << endl
            << endl;

        // now we can free the memory:
        delete[] Hashtable;
    }

    int Size() {
        return N;
    }

    //
    // Get
    //
    // Gets the data from the given index of the hash table: the Empty
    // status (T/F), the key, and the value.  If Empty is true, the key
    // and value will be the default values in C++ for their types.  If
    // the index is outside the bounds of the hashtable, the behavior
    // of this function is undefined.
    //
    void Get(int index, bool &empty, TKey &key, TValue &value) {
        _Probes++;

        empty = Hashtable[index].Empty;
        key = Hashtable[index].Key;
        value = Hashtable[index].Value;
    }

    //
    // Sets
    //
    // Sets the location of the hash table to contain the given key and
    // value; the "Empty" status is set to false since this location now
    // contains data.  Any existing data at this location is overwritten.
    // If the index is outside the bounds of the hashtable, the behavior
    // of this function is undefined.
    //
    void Set(int index, TKey key, TValue value) {
        _Stores++;

        Hashtable[index].Empty = false;
        Hashtable[index].Key = key;
        Hashtable[index].Value = value;
    }

    //
    // Keys
    //
    // Returns the keys in the hashtable, in order from 0..N-1.  Only
    // returns those keys where Empty is false.
    //
    vector<TKey> Keys() {
        vector<TKey> V;

        for (int i = 0; i < N; ++i)
            if (!Hashtable[i].Empty)
                V.push_back(Hashtable[i].Key);

        return V;
    }

    //
    // Values
    //
    // Returns the va.ues in the hashtable, in order from 0..N-1.  Only
    // returns those values where Empty is false.
    //
    vector<TValue> Values() {
        vector<TValue> V;

        for (int i = 0; i < N; ++i)
            if (!Hashtable[i].Empty)
                V.push_back(Hashtable[i].Value);

        return V;
    }

    //
    // Stats
    //
    // Returns some statistics about how the hashtable was used: # of
    // probes, # of stores, and # of elements currently in the table.
    //
    void Stats(int &probes, int &stores, int &elements) {
        probes = _Probes;
        stores = _Stores;

        elements = 0;
        for (int i = 0; i < N; ++i)
            if (!Hashtable[i].Empty)
                elements++;
    }

};


#endif /* hashtable_h */
