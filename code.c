/*

   Project
   E/18/010
   Avishka Abeywickrama

*/


#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>


//prototypes of functions
void clock_();
void patterns(int, int);
void signalhandler();


//global variables declaration
int fore_color, back_color;
int count = 1;



int main(int  argc, char ** argv){

	
	int flag1_pos = 0; //variable for first flag position

	//variables for color argumnets
	int color_arg1 = 0; 
       	int color_arg2 = 0;

	//find the first flag position
	for(int i=0; i < argc; i++){
	
	
		if(argv[i][0] == '-'){

			flag1_pos = i;
			break;

		}

		else{

			continue;

		}

	}	
	

	
	//check whether first flag is -h 	
	if(argv[flag1_pos][0] == '-' && argv[flag1_pos][1] == 'h'){
			
		printf("usage : clock -h \t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n");
      		printf("<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
		return 0;

	}	


	//check whether first flag is other one not -c, - and -- 
	else if(strcmp(argv[flag1_pos], "--") != 0 && (argv[flag1_pos][0] == '-' && argv[flag1_pos][1] != 'c' && strlen(argv[flag1_pos]) > 1)){
	
		printf("Invalid use of arguments.\n");
		printf("usage : clock -h \t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n");			   return 0;		

	}
	
	
	//check whether first flag is -c
	else if(argv[flag1_pos][0] == '-' && argv[flag1_pos][1] == 'c'){

		
		int x;

		//check for other flags and first flag
		for(int pos = flag1_pos; pos < argc;){
		

			//check for the argument only with -c
			if(strcmp(argv[pos], "-c") == 0){
			

				//check whether if it is the last argmunet
				if(pos + 1 == argc){
				
					printf("Invalid use of arguments.\n");
					printf("usage : clock -h \t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n");
					return 0;

				}

				
				//if not check for the next argument(color)
				else{
				
					color_arg1 = pos + 1; //store the position of the color argument1		
					

					//go to the next flag position(start from next position to the color argument1)
					for(x = color_arg1 + 1; x < argc; x++){
					
						if(argv[x][0] == '-' && strlen(argv[x]) != 1){

							break;
						}
					}

					pos = x; //assign the next flag position to pos
				}
			}

		
			//check for the argument -c with a color 
			else if(argv[pos][0] == '-' && argv[pos][1] == 'c' && strlen(argv[pos]) > 2){

                                color_arg2 = pos; //store the position of the color argument2


                                //go to the next flag position(start from next position)
                                for(x = pos + 1; x < argc; x++){

                                        if(argv[x][0] == '-' && strlen(argv[x]) != 1){

   						break;
      			  		}
                                }

				pos = x; //assign the next flag position to pos
                        }


			//check for the argument -h
			else if(argv[pos][0] == '-' && argv[pos][1] != '-' && argv[pos][1] == 'h'){

			 	printf("usage : clock -h \t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n");
               		       	printf("<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
        			return 0;
       
		       	}


			//check for the invalid arguments
		       	else if(strcmp(argv[pos], "--") != 0 && (argv[pos][0] == '-' && strlen(argv[pos]) > 1)){
										
				 printf("Invalid use of arguments.\n");		
			 	 printf("usage : clock -h \t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n");                   
				 return 0;

			}

			else{

				break;

			}

		}

	}
	

	//no flags(default colors)
	else{

		fore_color = 37;
		back_color = 47;
		
	}

	
	//convert color_arg1 to lowercase
	if(color_arg1 > 0){
	
		for(int y=0; y < strlen(argv[color_arg1]); y++){

			argv[color_arg1][y] = tolower(argv[color_arg1][y]); 

	 	}

	}

	//convert color_arg2 to lowercase
	if(color_arg2 > 0){

                for(int y=0; y < strlen(argv[color_arg2]); y++){

                        argv[color_arg2][y] = tolower(argv[color_arg2][y]); 

                }

        }


	//assign relevant background and foreground colors
	if(strcmp(argv[color_arg1], "black") == 0 || strcmp(argv[color_arg2], "-cblack") == 0){
	
		fore_color = 30;
		back_color = 40;

	}

	else if(strcmp(argv[color_arg1], "red") == 0 || strcmp(argv[color_arg2], "-cred") == 0){
	
		fore_color = 31;                                
		back_color = 41;

	}

	
	else if(strcmp(argv[color_arg1], "green") == 0 || strcmp(argv[color_arg2], "-cgreen") == 0){
		
		fore_color = 32;                       
		back_color = 42;
		
	}

		
	else if(strcmp(argv[color_arg1], "yellow") == 0 || strcmp(argv[color_arg2], "-cyellow") == 0){
	
		fore_color = 33;
		back_color = 43;

	}

		
	else if(strcmp(argv[color_arg1], "blue") == 0 || strcmp(argv[color_arg2], "-cblue") == 0){
                		
		fore_color = 34;                                			
		back_color = 44;
		
	}

	
	else if(strcmp(argv[color_arg1], "magenta") == 0 || strcmp(argv[color_arg2], "-cmagenta") == 0){
                		
		fore_color = 35;
		back_color = 45;
	}

	
	else if(strcmp(argv[color_arg1], "cyan") == 0 || strcmp(argv[color_arg2], "-ccyan") == 0){
    		
		fore_color = 36;                                
		back_color = 46;

	}

	
	else if(strcmp(argv[color_arg1], "white") == 0 || strcmp(argv[color_arg2], "-cwhite") == 0){
		
		fore_color = 37;	
		back_color = 47;	

	}

	
	//not a matching color argumnet in color_arg1	
	else if(color_arg1 > 0){

		for(int y=0; y < strlen(argv[color_arg1]); y++){
				
			printf("%c", argv[color_arg1][y]); //print the invalid color                       

		}			

		printf(" :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n");

		return 0;
	}


	//not a matching color argumnet in color_arg2	
	else if(color_arg2 > 0){

		for(int z=2; z < strlen(argv[color_arg2]); z++){
			       						
			printf("%c", argv[color_arg2][z]); //print the invalid color	

		}

		printf(" :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n");

		return 0;
	}       



	printf("\x1b[?1049h\x1b[?25l"); //open alternative screen and hide the cursor
	clock_(); //call the clock_ funcion
	printf("\x1b[?1049l\x1b[?25h"); //close alternative screen and visible the curso

	return 0;

}


//function to print the clock
void clock_(){

	time_t current_time;
	struct tm tm;


	signal(SIGINT, signalhandler); //handle ctrl+c


	//infinitely print the clock
	while(count){

	
		printf("\x1b[1J");
		//get current time and local time
		current_time = time(NULL);
        	tm = *localtime(&current_time);


		//print hours and change the cursor position
		patterns(tm.tm_hour/10, 2);
		patterns(tm.tm_hour%10, 9);
		

		//print the separation squares in the clock
		patterns(-1, 17);

		//print minutes and change the cursor position
		patterns(tm.tm_min/10, 21);
		patterns(tm.tm_min%10, 28);
		

		//print the separation squares in the clock
		patterns(-1, 36);
		
		//print seconds and change the cursor position
		patterns(tm.tm_sec/10, 40);
		patterns(tm.tm_sec%10, 47);

		
		//print the date
        	printf("\x1b[8;23H\x1b[%im%04d-%02d-%02d\n", fore_color,tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
        	

		sleep(1); //sleep clock for 1 second
				
	}
	
	printf("\x1b[0;m"); //reset

}


//design the numbers with small squares
void patterns(int num, int col){

	int line;

	//printing separation squares
	if(num == -1){
	
		printf("\x1b[3;%iH\x1b[%im  \x1b[0m\n\n", col,back_color);
		printf("\x1b[5;%iH\x1b[%im  \x1b[0m\n\n", col,back_color);

	}

	//printing zero
	if(num == 0){

		printf("\x1b[2;%iH\x1b[%im      \x1b[0m\n", col,back_color);

		for(int line=3; line < 6; line++){
		
			 printf("\x1b[%i;%iH\x1b[%im  \x1b[0m  \x1b[%im  \x1b[0m\n", line,col,back_color,back_color);
		
		}
	       	
		printf("\x1b[6;%iH\x1b[%im      \x1b[0m\n", col,back_color);
	
	}
	
	//printing one
	else if(num == 1){
	
		col = col + 4;
		
		for(line=2; line < 7; line++){
		
			printf("\x1b[%i;%iH\x1b[%im  \x1b[0m\n", line,col,back_color);
					
		}	

	}

	//printing two
	else if(num == 2){
	
		for(line=2; line < 7; line++){
		
			if(line%2 == 0){
			
                		printf("\x1b[%i;%iH\x1b[%im      \x1b[0m\n", line,col,back_color);

			}

			else if(line == 5){
			
                                printf("\x1b[%i;%iH\x1b[%im  \x1b[0m\n", line,col,back_color);
			
			}

			else{
		
                		printf("\x1b[%i;%iH    \x1b[%im  \x1b[0m\n", line,col,back_color);
			
			}
		}
	}


	//printing three
	else if(num == 3){
	
		for(line=2; line < 7; line++){

                        if(line%2 == 0){

                                printf("\x1b[%i;%iH\x1b[%im      \x1b[0m\n", line,col,back_color);

                        }

                        else{

                                printf("\x1b[%i;%iH    \x1b[%im  \x1b[0m\n", line,col,back_color);

                        }

		} 
	
	}
	

	//printing four
	else if(num == 4){
		
		printf("\x1b[2;%iH\x1b[%im  \x1b[0m  \x1b[%im  \x1b[0m\n", col,back_color,back_color);
	        printf("\x1b[3;%iH\x1b[%im  \x1b[0m  \x1b[%im  \x1b[0m\n", col,back_color,back_color);
		printf("\x1b[4;%iH\x1b[%im      \x1b[0m\n", col,back_color);
	   	printf("\x1b[5;%iH    \x1b[%im  \x1b[0m\n", col,back_color);
		printf("\x1b[6;%iH    \x1b[%im  \x1b[0m\n", col,back_color);	

	}


	//printing five
	else if(num== 5){
	
		printf("\x1b[2;%iH\x1b[%im      \x1b[0m\n", col,back_color);
	        printf("\x1b[3;%iH\x1b[%im  \x1b[0m\n", col,back_color); 
		printf("\x1b[4;%iH\x1b[%im      \x1b[0m\n", col,back_color);
	   	printf("\x1b[5;%iH    \x1b[%im  \x1b[0m\n", col,back_color);
	       	printf("\x1b[6;%iH\x1b[%im      \x1b[0m\n", col,back_color);

	}


	//printing six
	else if(num == 6){
	
                printf("\x1b[2;%iH\x1b[%im      \x1b[0m\n", col,back_color);
                printf("\x1b[3;%iH\x1b[%im  \x1b[0m\n", col,back_color);
                printf("\x1b[4;%iH\x1b[%im      \x1b[0m\n", col,back_color);
                printf("\x1b[5;%iH\x1b[%im  \x1b[0m  \x1b[%im  \x1b[0m\n", col,back_color,back_color);
                printf("\x1b[6;%iH\x1b[%im      \x1b[0m\n", col,back_color);
	
	}


	//printing seven
	else if(num == 7){
			
		printf("\x1b[2;%iH\x1b[%im      \x1b[0m\n", col,back_color);

		for(line=3; line < 7; line++){

                        printf("\x1b[%i;%iH    \x1b[%im  \x1b[0m\n", line,col,back_color);

                }
	
	}


	//printing eight
	else if(num == 8){
	        
                printf("\x1b[2;%iH\x1b[%im      \x1b[0m\n", col,back_color);
                printf("\x1b[3;%iH\x1b[%im  \x1b[0m  \x1b[%im  \x1b[0m\n", col,back_color,back_color);
                printf("\x1b[4;%iH\x1b[%im      \x1b[0m\n", col,back_color);
                printf("\x1b[5;%iH\x1b[%im  \x1b[0m  \x1b[%im  \x1b[0m\n", col,back_color,back_color);
                printf("\x1b[6;%iH\x1b[%im      \x1b[0m\n", col,back_color);

	}

	
	//printing nine
	else if(num == 9){
	
                printf("\x1b[2;%iH\x1b[%im      \x1b[0m\n", col,back_color);
                printf("\x1b[3;%iH\x1b[%im  \x1b[0m  \x1b[%im  \x1b[0m\n", col,back_color,back_color);
                printf("\x1b[4;%iH\x1b[%im      \x1b[0m\n", col,back_color);
                printf("\x1b[5;%iH    \x1b[%im  \x1b[0m\n", col,back_color);
                printf("\x1b[6;%iH\x1b[%im      \x1b[0m\n", col,back_color);

	}

	printf("\n");
}


//function to handle ctrl + c
void signalhandler(int signal){

	printf("\x1b[0m\x1b[1J");

	count = 0; //variable to stop the while loop
}

