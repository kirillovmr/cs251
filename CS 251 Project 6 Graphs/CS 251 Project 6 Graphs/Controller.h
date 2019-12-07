//
//  Controller.h
//  CS 251 Project 6 Graphs
//
//  Created by Viktor Kirillov on 11/25/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Controller_h
#define Controller_h

#include "minqueue.h"
#include "graph.h"

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

class Controller {
private:
    graph g;
    char input = ' ';
    string filename;
    vector<char> vertices, neighbors;
    
public:
    Controller() {
        cout << "Enter filename containing graph data> ";
        cin >> filename;
//        filename = "graph3.txt";
        if (!buildGraph())
            exit(0);
        
        vertices = g.vertices();
        cout << "\n**Vertices: ";
        for (char &v : vertices)
            cout << v << " ";
        
        cout << "\n**Edges: ";
        for (char &v : vertices) {
            neighbors = g.neighbors(v);
            for (char &n : neighbors)
                cout << "(" << v << "," << n << "," << g.getweight(v, n) << ") ";
        }
        cout << endl;
    }
    
    void loop() {
        while(true) {
            cout << "\nEnter a starting vertex or #> ";
            cin >> input;
            if (input == '#')
                break;
            
            if (!g.isvertex(input)) {
                cout << "Not a vertex in graph, ignored...";
                continue;
            }
            
            cout << "Neighbors: ";
            neighbors = g.neighbors(input);
            for (char &n : neighbors)
                cout << n << " ";
            
            cout << "\nBFS: ";
            neighbors = BFS(g, input);
            for (char &n : neighbors)
                cout << n << " ";
            
            cout << "\nDFS: ";
            neighbors = DFS(g, input);
            for (char &n : neighbors)
                cout << n << " ";
            
            cout << "\nDijkstra: ";
            map<char, int> distances, cameTo;
            neighbors = Dijkstra(g, input, distances, cameTo);
            
            for (char &n : neighbors)
                cout << n << " ";
            cout << endl;
            for (char &n : neighbors) {
                cout << " " << n << ": " << distances[n] << " via ";
                printPath(cameTo, n);
                cout << n << endl;
            }
        }
    }
    
private:
    void printPath(map<char, int> &cameTo, char dest) {
        if (cameTo[dest] == -1)
            return;
        printPath(cameTo, cameTo[dest]);
        cout << (char)cameTo[dest] << " ";
    }
    
    bool buildGraph() {
        ifstream file(filename);

        if (!file.good()) {
            cout << endl << "**Error: unable to open input file '" << filename << "'." << endl << endl;
            return false;
        }

        // Input vertices as single uppercase letters:  A B C ... #
        char a, b, v; int w;
        file >> v;
        while (v != '#') {
            g.addvertex(v);
            file >> v;
        }
    
        // Now input edges:  Src Dest Weight ... #
        file >> a;
        while (a != '#') {
            file >> b >> w;
            g.addedge(a,b,w);
            file >> a;
        }
        return true;
    }
    
    vector<char> BFS(graph &g, char &startV) {
        vector<char> visited, neighbors;
        queue<char> frontierQueue;
        set<char> discoveredSet;

        frontierQueue.push(startV);
        discoveredSet.insert(startV);
        while(frontierQueue.size()) {
            neighbors = g.neighbors( frontierQueue.front() );
            visited.push_back( frontierQueue.front() );
            frontierQueue.pop();
            for(char &n : neighbors) {
                if (discoveredSet.find(n) == discoveredSet.end()) {
                    frontierQueue.push(n);
                    discoveredSet.insert(n);
                }
            }
        }
        return visited;
    }
    
    vector<char> DFS(graph &g, char &startV) {
        vector<char> visited, neighbors;
        deque<char> frontierStack;
        set<char> visitedSet;

        frontierStack.push_back(startV);
        while(frontierStack.size()) {
            visited.push_back(frontierStack.back());
            visitedSet.insert(frontierStack.back());
            neighbors = g.neighbors(frontierStack.back()); frontierStack.pop_back();
            for(char &n : neighbors)
                if (visitedSet.find(n) == visitedSet.end())
                    if ( std::find(frontierStack.begin(), frontierStack.end(), n) == frontierStack.end() )
                        frontierStack.push_back(n);
        }
        return visited;
    }
    
    vector<char> Dijkstra(graph &g, char &startV, map<char, int> &distances, map<char, int> &cameTo) {
        vector<char> visited, neighbors;
        minqueue<char, int> minQ(30);
//        map<char, int> distances;
//        map<char, int> cameTo;
        
        for (char &v : g.vertices()) {
            minQ.pushinorder(v, INT_MAX);
            distances[v] = INT_MAX;
            cameTo[v] = -1;
        }
        
        minQ.pushinorder(startV, 0);
        distances[startV] = 0;
        
        while(!minQ.empty()) {
            int vDist;
            char v = minQ.minfront(vDist); minQ.minpop();
            if (vDist == INT_MAX)
                break;
            
            if (std::find(visited.begin(), visited.end(), v) == visited.end())
                visited.push_back(v);
            neighbors = g.neighbors(v);
            
            for (char &n : neighbors) {
                int edgeWeight = g.getweight(v, n);
                int alternativeDistance = vDist + edgeWeight;
                
                if (alternativeDistance < distances[n]) {
                    minQ.pushinorder(n, alternativeDistance);
                    distances[n] = alternativeDistance;
                    cameTo[n] = v;
                }
            }
        }
        
        return visited;
    }
};


#endif /* Controller_h */
