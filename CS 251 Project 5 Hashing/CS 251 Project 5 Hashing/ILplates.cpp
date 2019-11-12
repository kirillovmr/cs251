//
//  ILplates.cpp
//  CS 251 Project 5 Hashing
//
//  Hashing functions to store (license plate, amount) pairs
//  using linear probing.
//
//  Created by Viktor Kirillov on 11/11/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "ILplates.h"

#include <iostream>
#include <string>

using namespace std;

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters
//   and numbers.  Format: 1-5 letters plus 1..99 *OR*
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
//
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate) {
    int index = -1;

    size_t space = plate.find(" ");
    
    // Personalized
    if (space < plate.size()) {
        string let = plate.substr(0, space);
        string num = plate.substr(space+1);
        
        cout << let << ":" << num << endl;
        
        for (auto &c : let)
            if (c < 'A' || c > 'Z')
                return -1;
        
        for (auto &c : num)
            if (c < '0' || c > '9')
                return -1;
        
        // Case 1
        if (let.size() >= 1 && let.size() <= 5 && num.size() >= 1 && num.size() <= 2) {
            
        }
        // Case 2
        else if (let.size() == 6 && num.size() == 1) {
            
        }
        
    }
    
    // Vanity
    else {
        
        bool isNumber = plate[0] >= '0' && plate[0] <= '9' ? true : false;
        for (auto &c : plate) {
            if (isNumber && (c < '0' || c > '9'))
                return -1;
            else if (!isNumber && (c < 'A' || c > 'Z'))
                return -1;
        }
                    
        
        // Case 1
        if (plate.size() >= 1 && plate.size() <= 3) {
            
            
        }
        // Case 2
        else if (plate.size() >= 1 && plate.size() <= 7) {
            
        }
        cout << "vanity " << plate << endl;
    }
    
    cout << "ok\n";
    return index % HT.Size();
}


//
// Search
//
// Hashes and searches for the given license plate; returns the
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate) {
    //
    // TODO:
    //

    return -1;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue) {
    //
    // TODO:
    //
}
