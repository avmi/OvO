#include <iostream>
#include <stdexcept>


#include <cmath>
#include <limits>



bool almost_equal(float x, float y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<float>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<float>::min();

}



void test_target_teams__distribute__parallel_loop__simd(){

 // Input and Outputs
 
 const int L = 5;
 const int M = 6;
 const int N = 7;

float counter{};

// Main program

#pragma omp target teams  reduction(  +  :counter)   map(tofrom:counter) 

{


#pragma omp distribute  

    for (int i = 0 ; i < L ; i++ )

{


#pragma omp parallel loop  reduction(  +  :counter)  

    for (int j = 0 ; j < M ; j++ )

{


#pragma omp simd  reduction(  +  :counter)  

    for (int k = 0 ; k < N ; k++ )

{




counter += float { 1 };



}

}

}

}


// Validation
if ( !almost_equal(counter,float { L*M*N }, 10)  ) {
    std::cerr << "Expected: " << L*M*N << " Get: " << counter << std::endl;
    throw std::runtime_error( "target_teams__distribute__parallel_loop__simd give incorect value when offloaded");
}

}
int main()
{
    test_target_teams__distribute__parallel_loop__simd();
}