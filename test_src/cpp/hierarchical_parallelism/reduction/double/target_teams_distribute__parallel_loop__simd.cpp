#include <iostream>
#include <stdexcept>


#include <cmath>
#include <limits>



bool almost_equal(double x, double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<double>::min();

}



void test_target_teams_distribute__parallel_loop__simd(){

 // Input and Outputs
 
 const int L = 5;
 const int M = 6;
 const int N = 7;

double counter{};

// Main program

#pragma omp target teams distribute  reduction(  +  :counter)   map(tofrom:counter) 

    for (int i = 0 ; i < L ; i++ )

{


#pragma omp parallel loop  reduction(  +  :counter)  

    for (int j = 0 ; j < M ; j++ )

{


#pragma omp simd  reduction(  +  :counter)  

    for (int k = 0 ; k < N ; k++ )

{




counter += double { 1 };



}

}

}


// Validation
if ( !almost_equal(counter,double { L*M*N }, 10)  ) {
    std::cerr << "Expected: " << L*M*N << " Get: " << counter << std::endl;
    throw std::runtime_error( "target_teams_distribute__parallel_loop__simd give incorect value when offloaded");
}

}
int main()
{
    test_target_teams_distribute__parallel_loop__simd();
}