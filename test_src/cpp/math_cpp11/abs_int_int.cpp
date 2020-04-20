#include <cmath>
#include <limits>
#include <iostream>
#include <stdexcept>
#
using namespace std;
bool almost_equal(int x, int y, int ulp) {
    return x == y ; 
}
void test_abs(){
   int in0 {  1 };
   int out1_host;
   int out1_device;
    out1_host =  abs( in0);
   #pragma omp target map(from: out1_device )
   {
     out1_device =  abs( in0);
   }
   if ( !almost_equal(out1_host,out1_device,1) ) {
        std::cerr << "Host: " << out1_host << " GPU: " << out1_device << std::endl;
        throw std::runtime_error( "abs give incorect value when offloaded");
    }
}
int main()
{
    test_abs();
}
