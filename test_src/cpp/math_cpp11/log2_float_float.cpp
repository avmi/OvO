#include <cmath>
#include <limits>
#include <iostream>
#include <stdexcept>
#
using namespace std;
bool almost_equal(float x, float y, int ulp) {
     return std::fabs(x-y) <= std::numeric_limits<float>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<float>::min();
}
void test_log2(){
   float x {  0.42 };
   float o_host;
   float o_device;
    o_host =  log2( x);
   #pragma omp target map(from: o_device )
   {
     o_device =  log2( x);
   }
   if ( !almost_equal(o_host,o_device,1) ) {
        std::cerr << "Host: " << o_host << " GPU: " << o_device << std::endl;
        throw std::runtime_error( "log2 give incorect value when offloaded");
    }
}
int main()
{
    test_log2();
}
