#include <iostream>
#include <stdexcept>

#include <omp.h>




#include <cmath>
#include <limits>



bool almost_equal(double x, double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<double>::min();

}

void test_target__teams__parallel__for(){

 // Input and Outputs
 
 const int L = 5;

double counter{};

// Main program

#pragma omp target  map(tofrom:counter) 

{


#pragma omp teams 

{

const int num_teams = omp_get_num_teams();


#pragma omp parallel 

{


#pragma omp for 

    for (int i = 0 ; i < L ; i++ )

{



#pragma omp atomic update

counter += double { 1./num_teams } ;



}

}

}

}


// Validation
if ( !almost_equal(counter,double { L }, 1)  ) {
    std::cerr << "Expected: " << L << " Get: " << counter << std::endl;
    throw std::runtime_error( "target__teams__parallel__for give incorect value when offloaded");
}

}
int main()
{
    test_target__teams__parallel__for();
}