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
using namespace std;

int main(int argc, const char * argv[]) {
	int a = 3, b = 4;
	
	auto f = [a]() mutable -> int { return ++a; };
	auto g = [&,b]() -> int { return b; };
	
	a = 1; b = 2;
	
	cout << f() << endl;
	cout << g() << endl;
	
	return 0;
}
