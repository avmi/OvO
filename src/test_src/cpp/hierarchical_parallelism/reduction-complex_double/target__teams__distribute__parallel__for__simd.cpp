#include <iostream>
#include <cstdlib>
#include <cmath>
#include <complex>
using namespace std;
bool almost_equal(complex<double> x, complex<double> gold, float tol) {
        return abs(gold) * (1-tol) <= abs(x) && abs(x) <= abs(gold) * (1 + tol);
}
#pragma omp declare reduction(+: complex<double>: omp_out += omp_in)
void test_target__teams__distribute__parallel__for__simd(){
 const int N_i = 64;
 const int N_j = 64;
 const int N_k = 64;
 complex<double> counter{};
#pragma omp target map(tofrom: counter) 
#pragma omp teams reduction(+: counter)
#pragma omp distribute
    for (int i = 0 ; i < N_i ; i++ )
    {
#pragma omp parallel reduction(+: counter)
#pragma omp for
    for (int j = 0 ; j < N_j ; j++ )
    {
#pragma omp simd reduction(+: counter)
    for (int k = 0 ; k < N_k ; k++ )
    {
counter += complex<double> { 1.0f };
    }
    }
    }
if ( !almost_equal(counter,complex<double> { N_i*N_j*N_k }, 0.1)  ) {
    std::cerr << "Expected: " << N_i*N_j*N_k << " Got: " << counter << std::endl;
    std::exit(112);
}
}
int main()
{
    test_target__teams__distribute__parallel__for__simd();
}