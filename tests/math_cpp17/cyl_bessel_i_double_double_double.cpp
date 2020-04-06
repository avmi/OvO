
#include <cmath>


#include <limits>
#include <iostream>
#include <stdexcept>

using namespace std;

bool almost_equal(double x, double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<double>::min();

}

void test_cyl_bessel_i(){
   
   double nu {  0.42 };
   
   double x {  0.42 };
   

   double o_host = cyl_bessel_i( nu, x);

   double o_gpu ; 
   #pragma omp target map(from:o_gpu)
   {
   o_gpu = cyl_bessel_i( nu, x);
   }

   if ( !almost_equal(o_host,o_gpu,1) ) {
        std::cerr << "Host: " << o_host << " GPU: " << o_gpu << std::endl;
        throw std::runtime_error( "cyl_bessel_i give incorect value when offloaded");
    }
}

int main()
{
    test_cyl_bessel_i();
}
