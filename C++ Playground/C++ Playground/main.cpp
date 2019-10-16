//
//  main.cpp
//  C++ Playground
//
//  Created by Viktor Kirillov on 9/26/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric> // accumulate
#include <fstream>

#include "Quote.hpp"

using namespace std;

// calculate and print the price for the given number of copies, applying any discounts
double print_total(std::ostream &os, const Quote &item, size_t n) {
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << std::endl;
     return ret;
}

int main() {
    
    Bulk_quote book("book", 20, 10, 0.1);
    cout << book.net_price(10) << endl;
    print_total(cout, book, 11);

    return 0;
}
