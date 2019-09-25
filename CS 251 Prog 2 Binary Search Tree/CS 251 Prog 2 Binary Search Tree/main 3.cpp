//
// Viktor Kirillov
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.hpp"
#define DEBUG 1

using namespace std;

struct MovieData {
    int PubYear;
    int Num5Stars;
    int Num4Stars;
    int Num3Stars;
    int Num2Stars;
    int Num1Stars;
};

// trims whitespace from beginning and end of string.
string trim(const string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    
    if (first == string::npos && last == string::npos)  // empty, or all blanks:
        return "";
    else if (first == string::npos)  // no blanks at the start:
        first = 0;                     // 0-based
    else if (last == string::npos)   // no blanks trailing at end:
        last = str.length() - 1;       // 0-based
    
    return str.substr(first, (last - first + 1));
}



// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
void InputMovies(string moviesFilename, binarysearchtree<int, MovieData> &bst) {
    ifstream moviesFile(moviesFilename);
    int      id, pubYear;
    string   name;
    
    if (!moviesFile.good())
    {
        cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
        return;
    }
    
    moviesFile >> id;  // get first ID, or set EOF flag if file empty:
    
    while (!moviesFile.eof())
    {
        // we have more data, so input publication year and movie name:
        moviesFile >> pubYear;
        getline(moviesFile, name);  // movie name fills rest of input line:
        
        // trim potential whitespace from both ends of movie name:
        name = trim(name);
        
        // debugging:
//        cout << id << "," << pubYear << "," << name << endl;
        
        // inserting
        bst.insert(id, MovieData{pubYear,0,0,0,0,0});
        
        moviesFile >> id;  // get next ID, or set EOF flag if no more data:
    }
}

void displayBST(binarysearchtree<int, MovieData> bst) {
    bst.inorder();
    cout << bst.size() << " " << bst.height() << endl;
}


int main() {
	srand(1);
    binarysearchtree<int, MovieData> bst;
    
//    for (int i=0; i<30; i++) {
//        MovieData m{rand()%100,rand()%100,rand()%100,rand()%100,rand()%100,rand()%100};
//        bst.insert(rand()%1000, m);
//    }
//
//    bst.inorder();
//    cout << bst.size() << " " << bst.height() << endl;
//    displayBST(bst);
    
    string moviesFilename; // = "movies1.txt";
    string reviewsFilename; // = "reviews1.txt";
    
    cout << "movies file?> ";
    if (!DEBUG)
        cin >> moviesFilename;
    else
        moviesFilename = "movies1.txt";
    
    cout << "reviews file?> ";
    if (!DEBUG)
        cin >> reviewsFilename;
    else {
        reviewsFilename = "reviews1.txt";
        cout << endl;
    }
    
    string junk;
    if (!DEBUG)
        getline(cin, junk);  // discard EOL following last input:
    
    InputMovies(moviesFilename, bst);
    displayBST(bst);
    
    // done:
    return 0;
}
