//
//  m1.cpp
//  C++ Playground
//
//  Created by Viktor Kirillov on 10/13/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric> // accumulate
#include <fstream>

using namespace std;

typedef struct bookStruct {
    int id;
    string title;
} Book;

ostream& operator<<(ostream &os, Book &b) {
    os << b.id << ": " << b.title;
    return os;
}

istream &operator>>(istream &is, Book &b) {
    is >> b.id >> b.title;
    return is;
}

int func(int argc, const char * argv[]) {
    // Lambda
    int a = 3, b = 4;
    vector<int> vInt = {4,5,7,2,6,7};
    
    auto f = [a]() mutable -> int { return ++a; };
    auto g = [&,b]() -> int { return b; };
    auto disp = [](vector<int> &v) {
        for (auto a:v) cout << a << " ";
        cout << endl;
    };
    disp(vInt);
    
    int n = 5;
    int &&r = n * 5;
    
    cout << "r: " << r << endl;
    
    a = 1; b = 2;
    
    cout << f() << endl;
    cout << g() << endl;
    
    // Stream iterators
    ifstream str("a.txt");
    istream_iterator<int> in(str), out;
    cout << accumulate(in, out, 0) << endl;
    
    // Going at file start
    str.clear(); str.seekg(1);
    
    vector<int> vec(in, out);
    
    // Output iterator
    ostream_iterator<int> out_iter(cout, " ");

    for (auto &e : vec)
        *out_iter++ = e;
    cout << endl;
    //same as prev
    copy(vec.begin(), vec.end(), out_iter);
    cout << endl;
    
    // Jist another scope
    {
        int c = 3;
        cout << c << endl;
    }
    
    // Struct constructor
    typedef struct str{
        int a;
        str() {
            a = 4;
        }
    } struct1;
    
    struct1 s;
    cout << s.a << endl;
    
    if (int var = 0)
        cout << "Assignment" << endl;
    
    
    
    // OVERLOADING
    Book book = {123, "Harry"};
    Book book2;
    cout << "Enter book data (id title): ";
//    cin >> book2;
    cout << book << endl;
    
    plus<int> sum;
    cout << sum(1,2) << endl;
    
    return 0;
    
    
    
}

