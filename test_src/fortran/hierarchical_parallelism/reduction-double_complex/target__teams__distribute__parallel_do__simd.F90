FUNCTION almost_equal(x, gold, tol) RESULT(b)
  implicit none
  DOUBLE COMPLEX, intent(in) :: x
  INTEGER,  intent(in) :: gold
  REAL,     intent(in) :: tol
  LOGICAL              :: b
  b = ( gold * (1 - tol)  <= ABS(x) ).AND.( ABS(x) <= gold * (1+tol) )
END FUNCTION almost_equal
PROGRAM target__teams__distribute__parallel_do__simd
  implicit none
  INTEGER :: N0 = 64
  INTEGER :: i0
  INTEGER :: N1 = 64
  INTEGER :: i1
  INTEGER :: N2 = 64
  INTEGER :: i2
  LOGICAL :: almost_equal
  DOUBLE COMPLEX :: counter_N0
  INTEGER :: expected_value
  expected_value = N0*N1*N2
  counter_N0 = 0
  !$OMP target map(tofrom: counter_N0)
  !$OMP teams reduction(+: counter_N0)
  !$OMP distribute
  DO i0 = 1, N0
    !$OMP parallel do reduction(+: counter_N0)
    DO i1 = 1, N1
      !$OMP simd reduction(+: counter_N0)
      DO i2 = 1, N2
        counter_N0 = counter_N0 + 1.
      END DO
    END DO
  END DO
  !$OMP END teams
  !$OMP END target
  IF ( .NOT.almost_equal(counter_N0,expected_value, 0.1) ) THEN
    WRITE(*,*)  'Expected', expected_value,  'Got', counter_N0
    STOP 112
  ENDIF
END PROGRAM target__teams__distribute__parallel_do__simd
