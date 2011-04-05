/*
/* THIS file is used as a generator for random actions from six parts of 
   the system , [ collidence motor stablization navigation connectivity 
   camera ] , these actions will be either ( no_problem ) or ( problem )
   randomly , these actions will also show up randomly on the command line 
  
   
*/
 #include<stdio.h>
    #include"waw.h"
    
 void feed(int time_of_flying){
  
      int i;
      for(i=0;i<= time_of_flying;i++) {
			problem_faced();
                         
			 switch ( state_of_machine ) {
                                case 0:      
                                       no_colliedence_problems();
					
                                       break;
                                case 1:           
                                       colliedence_problems();
                                       break;
                                case 2:      
                                       no_motor_problems();
					
                                       break;
                                case 3:           
                                       motor_problems();
                                       break;
                                case 4:      
                                       no_Stablization_problems();
					
                                       break;
                                case 5:           
                                       Stablization_problems();
                                       break;
                                case 6:      
                                       no_Navigation_problems();
					
                                       break;
                                case 7:           
                                       Navigation_problems();
                                       break;
                                case 8:      
                                       no_Connectivity_problems();
					
                                       break;
                                case 9:           
                                       Connectivity_problems();
                                       break;
                                case 10:      
                                       no_Camera_problems();
					
                                       break;
                                case 11:           
                                       Camera_problems();
                                       break;
                              
                               default:             
                                     printf("Error, no data discovered \n");
                                        break;  
                                      } 

                              usleep(10000);
                    } 

     }

  void no_colliedence_problems()
           {
    printf( "OK \n");
           }
  void colliedence_problems()
           {
    printf( "Trip facing colliedence problems \n");
           }
  void  no_motor_problems()
           {
    printf( "OK \n");
           }
  void  motor_problems()
           {
    printf( "Trip facing motor problems \n");
           }
  void no_Stablization_problems()
           {
    printf( "OK  \n");
           }
  void Stablization_problems()
           {
    printf( "Trip facing stablization problems \n");
           }
  void no_Navigation_problems()
           {
    printf( "OK \n");
           }
  void Navigation_problems()
           {
    printf( "Trip facing colliedence problems \n");
           }
  void  no_Connectivity_problems()
           {
    printf( "OK \n");
           }
  void  Connectivity_problems()
           {
    printf( "Trip facing motor problems \n");
           }
  void no_Camera_problems()
           {
    printf( "OK  \n");
           }
  void Camera_problems()
           {
    printf( "Trip facing stablization problems \n");
           }


