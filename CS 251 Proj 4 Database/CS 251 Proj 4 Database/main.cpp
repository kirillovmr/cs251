//
//  main.cpp
//  CS 251 Proj 4 Database
//
//  Created by Viktor Kirillov on 10/22/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <string>
#include <iostream>
#include "Database.h"

int main(int argc, const char * argv[]) {
    
    std::string tablename;// = "students";

    std::cout << "Welcome to myDB, please enter tablename> ";
    getline(std::cin, tablename);
    
    Database db(tablename);
    db.loop();
    
    return 0;
}
