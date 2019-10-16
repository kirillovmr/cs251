//
//  Quote.hpp
//  C++ Playground
//
//  Created by Viktor Kirillov on 10/13/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#pragma once

#include <string>
#include <iostream>

class Quote {
private:
    std::string bookNo;
protected:
    double price = 0.0; // normal, undiscounted price
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price): bookNo(book), price(sales_price) { }
    
    std::string isbn() const { return bookNo; }
    
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const { return n * price; }
    
    // dynamic binding for the destructor
    virtual ~Quote() = default;
};

class Bulk_quote : public Quote {
private:
    std::size_t min_qty = 0; // minimum purchase for the discount to apply
    double discount = 0.0;   // fractional discount to apply
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p, std::size_t qty, double disc) :
        Quote(book, p), min_qty(qty), discount(disc) { }
    
    // overrides the base version in order to implement the bulk purchase discount policy
    double net_price(std::size_t) const override;
};

