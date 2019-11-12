//
//  ILplates.hpp
//  CS 251 Project 5 Hashing
//
//  Hashing functions to store (license plate, amount) pairs
//  using linear probing.  Implementation in associated .cpp
//  file.
//
//  Created by Viktor Kirillov on 11/11/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef ILplates_hpp
#define ILplates_hpp

#include <iostream>
#include <string>

#include "hashtable.h"

class ILplates {
private:
    hashtable<std::string, int> &HT;  // reference to underlying hashtable:

public:
    ILplates(hashtable<std::string, int> &ht) : HT(ht) {}

    int Hash(std::string plate);
    int Search(std::string plate);
    void Insert(std::string plate, int newValue);
};


#endif /* ILplates_hpp */
