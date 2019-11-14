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
#include <utility>
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
    
    // for each pair (fine, license plate), hash and store/update fine:
    while (!infile.eof()) {
        getline(infile, plate);

        total++;
        if (hashplates.Hash(plate) >= 0) { // yes:
            valid++;
            int amount = hashplates.Search(plate);

            if (amount < 0) {  // not found:
                hashplates.Insert(plate, stoi(fine));
            }
            else { // we found it, so update total in hash table:
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
    int N;// = 10000;
    string basename;// = "tickets2";

    cout << "Enter hashtable size> ";
    cin >> N;

    hashtable<string, int> ht(N);
    ILplates hashplates(ht);

    cout << "Enter base filename> ";
    cin >> basename;

    // process input file of fines and license plates:
    hashInput(basename, hashplates);

    vector<string> plates = ht.Keys();
    vector<int> amounts = ht.Values();
    vector<pair<string, int>> data;
    
    for (size_t i = 0; i < plates.size(); ++i)
        data.push_back({plates[i], amounts[i]});
    
    sort(data.begin(), data.end(), [](pair<string,int> &a, pair<string,int> &b){
        return a.first < b.first;
    });
    
    ofstream outfile(basename + "-output.txt");
    
    for (size_t i = 0; i < data.size(); ++i) {
        cout << data[i].first << ", " << data[i].second << endl;
        outfile << "\"" << data[i].first << "\"" << " $" << data[i].second << endl;
    }
    
    return 0;
}
