#include <iostream>
#include "bmp.h"

using std::cout;
using std::endl;

Buffer<int> foo(Buffer<int> a){
    return a;
}
Buffer<int*> foo(Buffer<int*> a){
    return a;
}


int main()
{
    bmpImage a("image.bmp");
}