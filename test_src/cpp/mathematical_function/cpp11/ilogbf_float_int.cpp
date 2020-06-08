#include <cmath>
#include <iomanip>
#include <limits>
#include <iostream>
#include <cstdlib>
using namespace std;
bool almost_equal(int x, int y, int ulp) {
    return x == y ;
}
void test_ilogbf(){
   float x {  0.42 };
   int o_host;
   int o_device;
    o_host =  ilogbf( x);
   #pragma omp target map(from: o_device )
   {
     o_device =  ilogbf( x);
   }
   if ( !almost_equal(o_host,o_device, 4) ) {
        std::cerr << std::setprecision (std::numeric_limits<int>::max_digits10 ) << "Host: " << o_host << " GPU: " << o_device << std::endl;
        std::exit(112);
    }
}
int main()
{
    test_ilogbf();
}
