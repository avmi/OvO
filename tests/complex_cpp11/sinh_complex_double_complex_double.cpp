
#include <complex>


#include <limits>
#include <iostream>
#include <stdexcept>

using namespace std;

bool almost_equal(complex<double> x, complex<double> y, int ulp) {

    bool r = std::fabs(x.real()-y.real()) <= std::numeric_limits<double>::epsilon() * std::fabs(x.real()+y.real()) * ulp ||  std::fabs(x.real()-y.real()) < std::numeric_limits<double>::min();
    bool i = std::fabs(x.imag()-y.imag()) <= std::numeric_limits<double>::epsilon() * std::fabs(x.imag()+y.imag()) * ulp ||  std::fabs(x.imag()-y.imag()) < std::numeric_limits<double>::min();
    return r && i;

}

void test_sinh(){
   
   complex<double> x {  0.42, 0.0 };
   

   complex<double> o_host = sinh( x);

   complex<double> o_gpu ; 
   #pragma omp target defaultmap(tofrom:scalar)
   {
   o_gpu = sinh( x);
   }

   if ( !almost_equal(o_host,o_gpu,1) ) {
        std::cerr << "Host: " << o_host << " GPU: " << o_gpu << std::endl;
        throw std::runtime_error( "sinh give incorect value when offloaded");
    }
}

int main()
{
    test_sinh();
}