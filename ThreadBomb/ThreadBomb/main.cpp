//
//  main.cpp
//  ThreadBomb
//
//  Created by Viktor Kirillov on 10/24/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <thread>

#define MAX_THREADS_SUPPORTED 8

void hello() {
    while (true) {
        std::cout << "Hello, Concurrent World!\n";
    }
}

int main(int argc, const char * argv[]) {
    int c = 0;
    while (c < MAX_THREADS_SUPPORTED * 8) {
        std::thread t(hello);
        if (c != MAX_THREADS_SUPPORTED - 1)
            t.detach();
        else
            t.join();
        c++;
    }
    return 0;
}
