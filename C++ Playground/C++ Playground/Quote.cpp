//
//  Quote.cpp
//  C++ Playground
//
//  Created by Viktor Kirillov on 10/13/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Quote.hpp"

double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}
