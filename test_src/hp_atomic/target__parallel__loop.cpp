#include <cassert>
#include <iostream>

template<class T>
void test_target__parallel__loop(){

 // Input and Outputs
 
 const int L = 5;

T counter{};

// Main program

#pragma omp target  map(tofrom: counter) 

{

#pragma omp parallel 

{

#pragma omp loop 

    for (int i = 0 ; i < L ; i++ )

{


#pragma omp atomic update
counter++;


}

}

}


// Validation
auto bo = ( counter == L ) ;
if ( bo != true) {
    std::cerr << "Expected: " << L << " Get: " << counter << std::endl;
    assert(bo);
}

}
int main()
{
    test_target__parallel__loop<double>();
}