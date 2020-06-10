#ifndef _OPENMP
FUNCTION omp_get_num_teams() RESULT(i)
    INTEGER :: i
    i = 1
END FUNCTION omp_get_num_teams
FUNCTION omp_get_num_threads() RESULT(i)
    INTEGER :: i
    i = 1
END FUNCTION omp_get_num_threads
#endif
FUNCTION almost_equal(x, gold, tol) RESULT(b)
    implicit none
    DOUBLE COMPLEX, intent(in) :: x
    INTEGER,  intent(in) :: gold
    REAL,     intent(in) :: tol
    LOGICAL              :: b
    b = ( gold * (1 - tol)  <= ABS(x) ).AND.( ABS(x) <= gold * (1+tol) )
END FUNCTION almost_equal
PROGRAM target_teams__parallel_do__simd
#ifdef _OPENMP
    USE OMP_LIB
    implicit none
#else
    implicit none
    INTEGER :: omp_get_num_teams
#endif
    LOGICAL :: almost_equal
    INTEGER :: N0 = 512
    INTEGER :: i0
    INTEGER :: N1 = 512
    INTEGER :: i1
    DOUBLE COMPLEX :: counter = (0,0)
    INTEGER :: num_teams
!$OMP TARGET TEAMS REDUCTION(+: counter) MAP(TOFROM: counter)
    num_teams = omp_get_num_teams()
!$OMP PARALLEL DO REDUCTION(+: counter)
       DO i0 = 1 , N0
!$OMP SIMD REDUCTION(+: counter)
       DO i1 = 1 , N1
counter = counter +  CMPLX(  1./num_teams , 0 )
    END DO
    END DO
!$OMP END TARGET TEAMS
IF ( .NOT.almost_equal(counter, N0*N1, 0.1) ) THEN
    WRITE(*,*)  'Expected', N0*N1,  'Got', counter
    CALL EXIT(112)
ENDIF
END PROGRAM target_teams__parallel_do__simd