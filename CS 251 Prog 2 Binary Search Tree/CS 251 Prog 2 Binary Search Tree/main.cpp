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
string trim(const string& str) {
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

void InputMovies(string moviesFilename, binarysearchtree<int, MovieData> &bstID, binarysearchtree<string, MovieData> &bstName) {
    ifstream moviesFile(moviesFilename);
    int      id, pubYear;
    string   name;
    
    if (!moviesFile.good()) {
        cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
        return;
    }
    
    moviesFile >> id;
    while (!moviesFile.eof()) {
        moviesFile >> pubYear;
		
        getline(moviesFile, name);
        name = trim(name);
		
		MovieData *data = new MovieData{pubYear,0,0,0,0,0};
        
        bstID.insert(id, MovieData{pubYear,0,0,0,0,0});
		bstName.insert(name, MovieData{pubYear,0,0,0,0,0});
        
        moviesFile >> id;
    }
	cout << "Num movies: " << bstID.size() << endl;
}

void inputRating(string filename, binarysearchtree<int, MovieData> &bstID, binarysearchtree<string, MovieData> &bstName) {
	ifstream reviewsFile(filename);
    int      reviewId, movieId, rating, numReviews = 0;
    string   name;
    
    if (!reviewsFile.good()) {
        cout << "**Error: unable to open movies file '" << filename << "', exiting" << endl;
        return;
    }
	
	reviewsFile >> reviewId;
	while (!reviewsFile.eof()) {
		reviewsFile >> movieId;
		reviewsFile >> rating;
		
		// inserting
		MovieData *dataID = bstID.search(movieId);
		if (dataID) {
			switch (rating) {
				case 1:
					dataID->Num1Stars++;
					break;
				case 2:
					dataID->Num2Stars++;
					break;
				case 3:
					dataID->Num3Stars++;
					break;
				case 4:
					dataID->Num4Stars++;
					break;
				case 5:
					dataID->Num5Stars++;
					break;
				default:
					break;
			}
		}
		
		reviewsFile >> reviewId;
		numReviews++;
	}
	cout << "Num reviews: " << numReviews << endl;
}

void displayBST(binarysearchtree<int, MovieData> bst) {
    bst.inorder();
    cout << bst.size() << " " << bst.height() << endl;
}


int main() {
    srand(1);
    binarysearchtree<int, MovieData> bstID;
	binarysearchtree<string, MovieData> bstName;
    
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
    
    InputMovies(moviesFilename, bstID, bstName);
	inputRating(reviewsFilename, bstID, bstName);
	
	cout << "\nTree by movie id: size=" << bstID.size() << ", height=" << bstID.height() << endl;
	cout << "Tree by movie name: size=" << bstName.size() << ", height=" << bstName.height() << endl;
	
	string input;
	while (true) {
		cout << "\nEnter a movie id or name (or # to quit)> ";
		getline(cin, input);
		trim(input);
		
		MovieData *data = bstName.search(input);
		if (!data) {
			cout << "not found..." << endl;
			continue;
		}
		
		cout << "Movie ID: " << 123 << endl
			<< "Movie Name: " << input << endl
			<< "Avg rating: " << 123 << endl
			<< "5 stars: " << data->Num5Stars << endl
			<< "4 stars: " << data->Num4Stars << endl
			<< "3 stars: " << data->Num3Stars << endl
			<< "2 stars: " << data->Num2Stars << endl
			<< "1 stars: " << data->Num1Stars << endl;
		
	}
    
    return 0;
}
