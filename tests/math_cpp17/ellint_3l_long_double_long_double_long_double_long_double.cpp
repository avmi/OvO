
#include <cmath>


#include <limits>
#include <iostream>
#include <stdexcept>

using namespace std;

bool almost_equal(long double x, long double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<long double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<long double>::min();

}

void test_ellint_3l(){
   
   long double k {  0.42 };
   
   long double nu {  0.42 };
   
   long double phi {  0.42 };
   

   long double o_host = ellint_3l( k, nu, phi);

   long double o_gpu ; 
   #pragma omp target map(from:o_gpu)
   {
   o_gpu = ellint_3l( k, nu, phi);
   }

   if ( !almost_equal(o_host,o_gpu,1) ) {
        std::cerr << "Host: " << o_host << " GPU: " << o_gpu << std::endl;
        throw std::runtime_error( "ellint_3l give incorect value when offloaded");
    }
}

int main()
{
    test_ellint_3l();
}
