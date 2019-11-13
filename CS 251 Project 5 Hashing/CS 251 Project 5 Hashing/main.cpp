//
//  main.cpp
//  CS 251 Project 5 Hashing
//
//  Created by Viktor Kirillov on 11/11/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;

void hashInput(string basename, ILplates &hashplates) {
    string infilename = basename + ".txt";
    ifstream infile(infilename);

    if (!infile.good()) {
        cout << endl;
        cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
        cout << endl;
        exit(-1);
    }

    cout << "Reading '" << infilename << "'..." << endl;
    
    string fine, plate;
    getline(infile, fine);
    
    int total = 0, valid = 0;
    //
    // for each pair (fine, license plate), hash and store/update fine:
    //
    while (!infile.eof()) {
        getline(infile, plate);

        //cout << fine << endl;
        //cout << plate << endl;

        //
        // is plate valid?  Only process valid plates:
        //
        cout << "Hash for " << plate << " is " << hashplates.Hash(plate) << endl;
        total++;
        if (hashplates.Hash(plate) >= 0) { // yes:
            valid++;
            int amount = hashplates.Search(plate);

            if (amount < 0) {  // not found:
//                cout << "Insert " << plate << endl;
                hashplates.Insert(plate, stoi(fine));
            }
            else { // we found it, so update total in hash table:
//                cout << "Update " << plate << endl;
                amount += stoi(fine);
                hashplates.Insert(plate, amount);
            }
        
        }//valid
        getline(infile, fine);
    }
    
    cout << "\nTotal plates: " << total << endl;
    cout << "# valid " << valid << endl;
    cout << "# invalid " << total - valid << endl;
}

int main() {
    int N = 10000;
    string basename = "tickets2";

    cout << "Enter hashtable size> ";
//    cin >> N;

    hashtable<string, int> ht(N);
    ILplates hashplates(ht);

    cout << "Enter base filename> ";
//    cin >> basename;
    cout << endl;

    // process input file of fines and license plates:
    hashInput(basename, hashplates);

    // debugging:
    vector<string> plates = ht.Keys();
    vector<int> amounts = ht.Values();

    for (size_t i = 0; i < plates.size(); ++i) {
        cout << plates[i] << ", " << amounts[i] << endl;
    }
    
    return 0;
}
