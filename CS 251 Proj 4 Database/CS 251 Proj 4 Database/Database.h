//
//  Database.hpp
//  CS 251 Proj 4 Database
//
//  Created by Viktor Kirillov on 10/22/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include "avl.h"

#include <map>
#include <queue>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

typedef avltree<std::string, std::streamoff> dbTree;

class Database {
private:
    std::string m_name;
    int m_offset, m_numCol;
    std::vector<std::string> m_columns, m_indexColumns;
    std::map<std::string, dbTree> m_trees;
    std::queue<std::thread> m_threads;
    std::vector<std::string> queryPattern{"select","%column_select","from","%table","where","%column_where","=","%value"};
    
    static void _buildTree(dbTree &tree, std::string filename, std::string colName, int offset, std::vector<std::string> &columns);
    static std::vector<std::streamoff> linearSearch(std::string tableName, std::string colName, std::vector<std::string> &columns, int offset, std::string matchValue);
    static std::vector<std::string> getEntry(std::string tableName, std::streamoff pos, size_t numColumns);
    static std::vector<std::string> tokenize(std::string input);
    
public:
    Database() = default;
    Database(std::string filename);
    
    void loop();
};

#endif /* Database_hpp */
