#include <iostream>
#include <cstdlib>
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_teams()   {return 1;}
int omp_get_num_threads() {return 1;}
#endif
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * (1 + tol);
}
void test_target__teams_distribute__parallel__simd(){
 const int N_i = 64;
 const int N_j = 64;
 float counter{};
#pragma omp target map(tofrom: counter) 
#pragma omp teams distribute reduction(+: counter)
    for (int i = 0 ; i < N_i ; i++ )
    {
#pragma omp parallel reduction(+: counter)
    {
const int num_threads = omp_get_num_threads();
#pragma omp simd reduction(+: counter)
    for (int j = 0 ; j < N_j ; j++ )
    {
counter += float { 1.0f/num_threads };
    }
    }
    }
if ( !almost_equal(counter,float { N_i*N_j }, 0.1)  ) {
    std::cerr << "Expected: " << N_i*N_j << " Got: " << counter << std::endl;
    std::exit(112);
}
}
int main()
{
    test_target__teams_distribute__parallel__simd();
}