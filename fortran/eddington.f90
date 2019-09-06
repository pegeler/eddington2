program eddington
    implicit none

    character(256) :: argv
    real, allocatable :: rides(:)
    integer :: n = 0
    
    ! Get file name
    call getarg(1, argv)
    
    ! Reading in the file
    open(unit=11, file=argv, status='old', action='read')
    
    ! Find the number of lines in the file
    do
        read(11, *, end=10)
        n = n + 1
    end do

    ! Allocate the space, rewind, and read in rides
10  allocate(rides(n))

    rewind(11)

    read(11, *) rides  
  
    close(11)
    
    ! Compute E and print result
    print *, E(rides, n)

contains

    ! Define function for calculating E
    integer function E(rides, n)
        implicit none
        
        integer, intent(in) :: n
        real, intent(in) :: rides(n)
        integer :: above, ride, i
        real :: H(n - 1)
        
        above = 0
        E = 0
        H = H*0
        
        do i = 1, n
        
            ride = int(rides(i))
            
            if (ride .gt. E) then
            
                above = above + 1
                
                if (ride .lt. n) then
                
                    H(ride) = H(ride) + 1
                    
                endif
                
                if (above .gt. E) then
                
                    E = E + 1
                    
                    if (E .lt. n) then

                        above = above - H(E)

                    endif
                
                endif
            
            endif
            
        end do
        
    end function E
  
end program eddington
