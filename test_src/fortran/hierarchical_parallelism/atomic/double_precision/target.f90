
program target
    USE OMP_LIB

    implicit none
  
    
    DOUBLE PRECISION :: COUNTER = 0

    
    

     
    
    !$OMP TARGET   MAP(TOFROM: COUNTER) 



    

    

!$OMP ATOMIC UPDATE

counter = counter + 1.


 
     

    !$OMP END TARGET
    

    IF  ( ( ABS(COUNTER - 1) ) > 10*EPSILON(COUNTER) ) THEN
        write(*,*)  'Expected 1 Got', COUNTER
        call exit(1)
    ENDIF

end program target