
program target__teams

    USE OMP_LIB

    

    implicit none
  
    
    REAL :: COUNTER =  0   

    
    INTEGER :: num_teams
    
    
     
    
    !$OMP TARGET    MAP(TOFROM: COUNTER) 



    

    
    !$OMP TEAMS   REDUCTION(+:COUNTER)  



    
    num_teams = omp_get_num_teams()
    

    


counter = counter +  1./num_teams  

 
     

    !$OMP END TEAMS
     

    !$OMP END TARGET
    

    IF  ( ( ABS(COUNTER - 1) ) > 10*EPSILON( COUNTER   ) ) THEN
        write(*,*)  'Expected 1 Got', COUNTER
        call exit(1)
    ENDIF

end program target__teams