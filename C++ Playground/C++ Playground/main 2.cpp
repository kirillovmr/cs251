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
#include <algorithm>

using namespace std;

int main(int argc, const char * argv[]) {
	
	cin.tie(nullptr);
	
//	cin >> a;
	
	cout << unitbuf;
	cout << "Line 1 " << endl;
	cout << "Line 2" << flush;
	cout << "Line 3\n" << ends;
	
	vector<int> vec;
	vec.push_back(2);
	cout << vec.max_size() << endl;
	
	vector<long> vec2;
	cout << vec2.max_size() << endl;
	
	cout << *find(vec.cbegin(), vec.cend(), 2) << endl;
	
	return 0;
}
