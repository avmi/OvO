program target__teams__distribute__parallel__loop

    

    implicit none

    DOUBLE COMPLEX, ALLOCATABLE :: A(:) 
    DOUBLE COMPLEX, ALLOCATABLE :: B(:)
    
    REAL, ALLOCATABLE :: B_real(:)
    REAL, ALLOCATABLE :: B_imag(:)
    

  
    INTEGER :: L = 5
    INTEGER :: i
    INTEGER :: M = 6
    INTEGER :: j

    INTEGER :: S
    S = L*M
     
    ALLOCATE(A(S), B(S) , B_real(S), B_imag(S)  )
       
    
    CALL RANDOM_NUMBER(B_real)
    CALL RANDOM_NUMBER(B_imag)
    B = cmplx(B_real,B_imag)
    DEALLOCATE (B_real,B_imag)
    

    
    !$OMP TARGET   MAP(FROM: A) MAP(TO: B) 


    
    !$OMP TEAMS 


    
    !$OMP DISTRIBUTE 


    DO i = 1 , L 

    
    !$OMP PARALLEL 


    
    !$OMP LOOP 


    DO j = 1 , M 

    

    A( j + (i-1)*M ) = B( j + (i-1)*M )
 
     

    END DO

    !$OMP END LOOP
     

    !$OMP END PARALLEL
     

    END DO

    !$OMP END DISTRIBUTE
     

    !$OMP END TEAMS
     

    !$OMP END TARGET
    

    IF (ANY(ABS(A - B) > EPSILON(  REAL(  B  )  ) )) THEN
        write(*,*)  'Wrong value', MAXVAL(ABS(A-B)), 'max difference'
        call exit(1)
    ENDIF

    DEALLOCATE(A,B)

end program target__teams__distribute__parallel__loop