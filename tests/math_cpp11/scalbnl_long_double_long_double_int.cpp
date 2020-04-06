
#include <cmath>


#include <limits>
#include <iostream>
#include <stdexcept>

using namespace std;

bool almost_equal(long double x, long double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<long double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<long double>::min();

}

void test_scalbnl(){
   
   long double x {  0.42 };
   
   int n {  1 };
   

   long double o_host = scalbnl( x, n);

   long double o_gpu ; 
   #pragma omp target map(from:o_gpu)
   {
   o_gpu = scalbnl( x, n);
   }

   if ( !almost_equal(o_host,o_gpu,1) ) {
        std::cerr << "Host: " << o_host << " GPU: " << o_gpu << std::endl;
        throw std::runtime_error( "scalbnl give incorect value when offloaded");
    }
}

int main()
{
    test_scalbnl();
}
