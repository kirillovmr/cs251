//
//  main.cpp
//  Concurrency
//
//  Created by Viktor Kirillov on 10/21/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

std::mutex locker;

void pushToVector(vector<char> &v, char b) {
    std::lock_guard<std::mutex> guard(locker);
    for (int i=0; i<50; i++) {
        v.push_back(b);
    }
}

int main(int argc, const char * argv[]) {
    
    vector<char> vec;
    
    thread t1(pushToVector, std::ref(vec), 'a');
    thread t2(pushToVector, std::ref(vec), 'b');
    
    t1.join();
    t2.join();
    
    cout << vec.size() << endl;
    
    return 0;
}
