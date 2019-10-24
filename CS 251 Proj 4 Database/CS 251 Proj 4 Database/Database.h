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

using std::map;
using std::queue;
using std::vector;
using std::string;
using std::thread;
using std::streamoff;

typedef avltree<string, streamoff> dbTree;

class Database {
private:
    string m_name;
    int m_offset, m_numCol;
    vector<string> m_columns, m_indexColumns;
    map<string, dbTree> m_trees;
    queue<thread> m_threads;
    vector<string> queryPattern{"select","%column_select","from","%table","where","%column_where","=","%value"};
    
    static void _buildTree(dbTree &tree, string filename, string colName, int offset, vector<string> &columns);
    static vector<streamoff> linearSearch(string tableName, string colName, vector<string> &columns, int offset, string matchValue);
    static vector<string> getEntry(string tableName, streamoff pos, size_t numColumns);
    static vector<string> tokenize(string input);
    
public:
    Database() = default;
    Database(string filename);
    
    void loop();
};

#endif /* Database_hpp */
