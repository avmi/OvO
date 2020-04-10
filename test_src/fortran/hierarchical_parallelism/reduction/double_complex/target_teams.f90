
program target_teams

    USE OMP_LIB

    

    implicit none
  
    
    DOUBLE COMPLEX :: COUNTER =  (    0   ,0)  

    
    INTEGER :: num_teams
    
    
     
    
    !$OMP TARGET TEAMS   REDUCTION(+:COUNTER)   MAP(TOFROM: COUNTER) 



    
    num_teams = omp_get_num_teams()
    

    


counter = counter +  CMPLX(   1./num_teams   ,0) 

 
     

    !$OMP END TARGET TEAMS
    

    IF  ( ( ABS(COUNTER - 1) ) > 10*EPSILON( REAL(  COUNTER  )   ) ) THEN
        write(*,*)  'Expected 1 Got', COUNTER
        call exit(1)
    ENDIF

end program target_teams