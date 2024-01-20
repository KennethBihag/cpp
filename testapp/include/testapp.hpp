#ifndef TESTAPP_H
#define TESTAPP_H

#include <iostream>

using std::cout;
using std::endl;

struct TestApp{
	TestApp(){
		cout << "TestApp created" << endl;
	}
	~TestApp(){
		cout << "TestApp destroyed" << endl;
	}
};

#endif