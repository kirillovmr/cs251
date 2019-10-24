//
//  Database.cpp
//  CS 251 Proj 4 Database
//
//  Created by Viktor Kirillov on 10/22/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Database.h"

#define CHECK_FOR_GOOD_FILE(data, tableName) if (!data.good()) { cout << "**Error: couldn't open data file '" << tableName << "'." << endl; return; }
#define CHECK_FOR_GOOD_FILE_RET(data, tableName, returnVal) if (!data.good()) { cout << "**Error: couldn't open data file '" << tableName << "'." << endl; return returnVal; }
#define PRINT_ERROR_BREAK(error) { cout << error << endl; break; }

using namespace std;

Database::Database(string filename) : m_name(filename) {
    string colName; int num;
    
    cout << "Reading meta-data..." << endl;
    ifstream data(filename + ".meta", ios::in | ios::binary);
    CHECK_FOR_GOOD_FILE(data, filename);
    
    data >> m_offset >> m_numCol;
    for (int i=0; i<m_numCol; i++) {
        data >> colName >> num;
        m_columns.push_back(colName);
        if (num == 1)
            m_indexColumns.push_back(colName);
    }
    
    cout << "Building index tree(s)..." << endl;
    int maxThreads = std::max(8, static_cast<int>(thread::hardware_concurrency()));
    for (auto &col: m_indexColumns) {
        if (m_threads.size() == maxThreads) {
            m_threads.front().join();
            m_threads.pop();
        }
        m_threads.push( thread(_buildTree, std::ref(m_trees[col]), filename, col, m_offset, std::ref(m_columns)) );
    }
    
    while (m_threads.size()) {
        m_threads.front().join();
        m_threads.pop();
    }
    
    for (auto &c : m_indexColumns)
        cout << "Index column: " << c << endl << "  Tree size: " << m_trees[c].size() << endl << "  Tree height: " << m_trees[c].height() << endl;
    
}

void Database::_buildTree(dbTree &tree, string filename, string colName, int offset, vector<string> &columns) {
    
    ifstream data(filename + ".data", ios::in | ios::binary);
    CHECK_FOR_GOOD_FILE(data, filename)
    
    // move to the end to get length of file:
    data.seekg(0, data.end);
    streamoff length = data.tellg(), pos;
    string value;
    
    for (pos = 0; pos < length; pos += offset) {
        data.seekg(pos, data.beg);
        for (int i=0; i<columns.size(); i++) {
            data >> value;
            if (colName == columns[i]) {
                tree.insert(value, pos); break;
            }
        }
    }

}

vector<string> Database::tokenize(string input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    
    while(getline(ss, token, ' '))
        tokens.push_back(token);
    
    return tokens;
}

vector<string> Database::getEntry(string tableName, streamoff pos, size_t numColumns) {
    vector<string> entry;
    string value;
    
    ifstream data(tableName + ".data", ios::in | ios::binary);
    CHECK_FOR_GOOD_FILE_RET(data, tableName, entry)

    data.seekg(pos, data.beg);
    for (int i=0; i<numColumns; i++) {
        data >> value;
        entry.push_back(value);
    }
    return entry;
}

vector<streamoff> Database::linearSearch(string tableName, string colName, vector<string> &columns, int offset, string matchValue) {
    vector<streamoff> matches;
    
    ifstream data(tableName + ".data", ios::in | ios::binary);
    CHECK_FOR_GOOD_FILE_RET(data, tableName, matches)
    
    // move to the end to get length of file:
    data.seekg(0, data.end);
    streamoff length = data.tellg(), pos;
    string value;

    for (pos = 0; pos < length; pos += offset) {
        data.seekg(pos, data.beg);
        for (int i=0; i<columns.size(); i++) {
            data >> value;
            if (colName == columns[i] && value == matchValue) {
                matches.push_back(pos); break;
            }
        }
    }
    return matches;
}

void Database::loop() {
    vector<string> tokens;
    string query;
    
    while(true) {
        cout << "\nEnter query> ";
        getline(cin, query);
        
        if (query == "exit") break;
        
        tokens = tokenize(query);
        for (int i=0; i<tokens.size(); i++) {
            if (i % 2 == 0 && tokens[i] != queryPattern[i]){
                i == 0 ? cout << "Unknown query, ignored..." << endl : cout << "Invalid select query, ignored..." << endl;
                break;
            }
            else {
                if (i == 1 && tokens[i] != "*" && find(m_columns.begin(), m_columns.end(), tokens[i]) == m_columns.end())
                    PRINT_ERROR_BREAK("Invalid select column, ignored...")
                else if (i == 3 && tokens[i] != m_name)
                    PRINT_ERROR_BREAK("Invalid table name, ignored...")
                else if (i == 5 && find(m_columns.begin(), m_columns.end(), tokens[i]) == m_columns.end())
                    PRINT_ERROR_BREAK("Invalid where column, ignored...")
            }
            
            // If here - query is valid
            if (i == tokens.size() - 1) {
                vector<streamoff> posV;
                
                // If WHERE is indexed
                if (find(m_indexColumns.begin(), m_indexColumns.end(), tokens[5]) != m_indexColumns.end()) {
                    streamoff *pos = m_trees[tokens[5]].search(tokens[7]);
                    if (pos != nullptr)
                        posV.push_back(*pos);
                }
                else
                    posV = linearSearch(m_name, tokens[5], m_columns, m_offset, tokens[7]);
                
                if (!posV.size())
                    cout << "Not found..." << endl;
                   
                for (auto p : posV) {
                    vector<string> res = getEntry(m_name, p, m_columns.size());
                    for (int i=0; i<res.size(); i++)
                        if (tokens[1] == "*" || tokens[1] == m_columns[i])
                            cout << m_columns[i] << ": " << res[i] << endl;
                }
            }
        }
    }
}
