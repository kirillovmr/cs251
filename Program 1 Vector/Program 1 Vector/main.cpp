//
// Project #01: input movie review data from a file, and output moviename, # of
// reviews, average review, and # of reviews per star.
//
// File example "movie1.txt":
//   Finding Nemo
//   5
//   4
//   5
//   4
//   5
//   -1
//
// Output:
//  Movie: Finding Nemo
//  Num reviews: 5
//  Avg review:  4.6
//  5 stars: 3
//  4 stars: 2
//  3 stars: 0
//  2 stars: 0
//  1 star:  0
//

#include <iostream>
#include <fstream>
#include <string>

#include "myvector.h"

using namespace std;

// functions from student.cpp:
myvector<int> InputData(string filename, string& moviename);
double   GetAverage(myvector<int> reviews);
myvector<int> GetNumStars(myvector<int> reviews);

void copytest(myvector<int> v) {
    cout << "TEST COPY:\n";
    for (int i=0; i<v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
    
    int size = v.size();
    for (int i=0; i<size; i++)
        v.erase(0);
    
    for (int i=7; i<13; i++)
        v.push_back(i);
    v.push_back(33);
    
    for (int i=0; i<v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

int main()
{
    myvector<int>  reviews;
    myvector<int>  numstars;
    double    avg;
    string    filename, moviename;
    
//    for (int i=0; i<5; i++)
//        reviews.push_back(i);
//
//    copytest(reviews);
    
//    for (int i=0; i<1000000; i++)
//        if (i > 999990)
//            cout << reviews[i] << " ";
//    cout << endl;
    
    //
    // 1. input filename and then the review data:
    //
//    cin >> filename;
    filename = "movie3.txt";

    reviews = InputData(filename, moviename);

    cout << "Movie: " << moviename << endl;
    cout << "Num reviews: " << reviews.size() << endl;

    //
    // 2. average review
    //
    avg = GetAverage(reviews);
    cout << "Avg review:  " << avg << endl;

    //
    // 3. # of 5 stars, 4 stars, etc
    //
    numstars = GetNumStars(reviews);

    for (int i = numstars.size(); i > 0; --i)
    {
        //
        // i is 5, 4, 3, 2, 1:
        //
        if (i == 1)
            cout << i << " star:  " << numstars[i - 1] << endl;
        else
            cout << i << " stars: " << numstars[i - 1] << endl;
    }

    return 0;
}
