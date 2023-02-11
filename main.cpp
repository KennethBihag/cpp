#include <iostream>
#ifdef _USE_API_
#define _MYGUID_API_
#endif
#include "MyGUID.hpp"
using std::cout;

void main(){
    cout << "Program is working fine with size of short: "<<
       sizeof(short)<<"; int:" << sizeof(int) <<
       "; long: "<< sizeof(long)<<"; and long long: "<<sizeof(long long) << '\n';
    MyGUID guid;
    guid.GenGUID();
    cout << guid.String();
}