#include <iostream>
#include "MyGUID.hpp"
using std::cout;

void main(){
    cout << "Program is working fine.\n";
    MyGUID guid;
    guid.GenGUID();
    cout << guid.String();
}