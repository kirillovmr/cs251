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
#include <cctype>
#include <algorithm>
#include "bst.hpp"
#define DEBUG 1

using namespace std;

struct MovieData {
	string name;
    int PubYear, id;
	int numStars[5];
};

// trims whitespace from beginning and end of string.
string trim(const string &str) {
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

void InputMovies(const string &moviesFilename, binarysearchtree<int, MovieData> &bstID, binarysearchtree<string, MovieData> &bstName) {
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
		
		MovieData *data = new MovieData{name, pubYear, id, 0,0,0,0,0};
        
        bstID.insert(id, data);
		bstName.insert(name, data);
        
        moviesFile >> id;
    }
	cout << "Num movies: " << bstID.size() << endl;
}

void inputRating(const string &filename, binarysearchtree<int, MovieData> &bstID) {
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
		MovieData **dataID = bstID.search(movieId);
		if (dataID)
			(*dataID)->numStars[rating-1]++;
		
		reviewsFile >> reviewId;
		numReviews++;
	}
	cout << "Num reviews: " << numReviews << endl;
}

bool isThereCharacter(string &input) {
	for (auto &c : input)
		if (isalpha(c))
			return true;
	return false;
}


int main() {
    binarysearchtree<int, MovieData> bstID;
	binarysearchtree<string, MovieData> bstName;
    string moviesFilename, reviewsFilename, input;
	MovieData **data;
    
	if (!DEBUG) {
		cout << "movies file?> ";
        cin >> moviesFilename;
		cout << "reviews file?> ";
		cin >> reviewsFilename;
		getline(cin, input);  // discard EOL following last input:
		cout << endl;
	} else {
        moviesFilename = "movies1.txt";
		reviewsFilename = "reviews1.txt";
	}
    
    InputMovies(moviesFilename, bstID, bstName);
	inputRating(reviewsFilename, bstID);
	
	cout << "\nTree by movie id: size=" << bstID.size() << ", height=" << bstID.height() << endl;
	cout << "Tree by movie name: size=" << bstName.size() << ", height=" << bstName.height() << endl;
	
	while (true) {
		cout << "\nEnter a movie id or name (or # to quit)> ";
		getline(cin, input);
		trim(input);
		
		if(input == "#")
			exit(0);
		
		data = isThereCharacter(input) ? bstName.search(input) : bstID.search(atoi(input.c_str()));
		
		if (!data) {
			cout << "not found..." << endl;
			continue;
		}
		
		auto avgRating = [data] {
			double r = (5.0*(*data)->numStars[4] + 4*(*data)->numStars[3] + 3*(*data)->numStars[2] + 2*(*data)->numStars[1] + (*data)->numStars[0])
					/ ((*data)->numStars[4] + (*data)->numStars[3] + (*data)->numStars[2] + (*data)->numStars[1] + (*data)->numStars[0]);
			return r > 0 ? r : 0;
		};
		
		cout << "Movie ID: " << (*data)->id << endl
			<< "Movie Name: " << (*data)->name << endl
			<< "Avg rating: " << avgRating() << endl
			<< "5 stars: " << (*data)->numStars[4] << endl
			<< "4 stars: " << (*data)->numStars[3] << endl
			<< "3 stars: " << (*data)->numStars[2] << endl
			<< "2 stars: " << (*data)->numStars[1] << endl
			<< "1 stars: " << (*data)->numStars[0] << endl;
	}
    
    return 0;
}
