FUNCTION almost_equal(x, gold, tol) RESULT(b)
    implicit none
    DOUBLE COMPLEX, intent(in) :: x
    INTEGER,  intent(in) :: gold
    REAL,     intent(in) :: tol
    LOGICAL              :: b
    b = ( gold * (1 - tol)  <= ABS(x) ).AND.( ABS(x) <= gold * (1+tol) )
END FUNCTION almost_equal
PROGRAM target_parallel__do
    LOGICAL :: almost_equal
    INTEGER :: N0 = 262144
    INTEGER :: i0
    DOUBLE COMPLEX :: counter = (0,0)
!$OMP TARGET PARALLEL REDUCTION(+: counter) MAP(TOFROM: counter)
!$OMP DO
       DO i0 = 1 , N0
counter = counter +  CMPLX(  1. , 0 )
    END DO
!$OMP END TARGET PARALLEL
IF ( .NOT.almost_equal(counter, N0, 0.1) ) THEN
    WRITE(*,*)  'Expected', N0,  'Got', counter
    CALL EXIT(112)
ENDIF
END PROGRAM target_parallel__do