/* This files provides address values that exist in the system */

#define SDRAM_BASE            0xC0000000
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_CHAR_BASE        0xC9000000

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define TIMER_BASE            0xFF202000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030
#define PS2_BASE 0xFF200100	

/* VGA colors */
#define WHITE 0xFFFF
#define YELLOW 0xFFE0
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define GREY 0xC618
#define PINK 0xFC18
#define ORANGE 0xFC00

#define ABS(x) (((x) > 0) ? (x) : -(x))

/* Screen size. */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

/* Constants for animation */
#define BOX_LEN 4
#define NUM_BOXES 8

#define FALSE 0
#define TRUE 1

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Global Variables

bool introScreen = true;


char * firstPlayerScore = "0";
char * secondPlayerScore = "0";
	
	
	
//function declarations	
volatile int pixel_buffer_start; // global variable
void plot_pixel(int x, int y, short int line_color);
void clear_screen();
void wait_for_vsync();
void draw_bead(int x, int y, int r, short int clr);
void draw_heap(int heapX, int numBeads, int rad, short int clr);
int keyBoardInput();

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    // declare other variables(not shown)
	short int color[] = {YELLOW, RED, PINK, BLUE, CYAN, MAGENTA, GREEN, ORANGE};
	
	int colNum;
	int numPieces;
	bool twoPlayerMode = false;
	bool aiMode = false;
	
	bool d = true; //true is player 1, false is player 2
	int playerNum;
	int firstPlayerCounter = 0;
    int secondPlayerCounter = 0;
    
	int heap1 = 1;
	int heap2 = 3;
	int heap3 = 5;
	int heap4 = 7;
	int heap5 = 9;
	

	short int heap1clr;
	short int heap2clr;
	short int heap3clr;
	short int heap4clr;
	short int heap5clr;
	
	int heap1x = -1;
	int heap2x = -1;
	int heap3x = -1;
	int heap4x = -1;
	int heap5x = -1;
	
	int numHeaps = 5;

    /* set front pixel buffer to start of FPGA On-chip memory */
    *(pixel_ctrl_ptr + 1) = FPGA_ONCHIP_BASE; // first store the address in the 
                                        // back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = SDRAM_BASE;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
	
	clear_screen(); //x_resolution = 320
	
	
    while (1){  
		//clear_char();
		if(introScreen){
 heap1 = 1;
 heap2 = 3;
heap3 = 5;
 heap4 = 7;
 heap5 = 9;
heap1x = -1;
	heap2x = -1;
	heap3x = -1;
	heap4x = -1;
	heap5x = -1;
			
	numHeaps = 5;
			
	int seed = rand() % 8;
	heap1clr = color[seed];
	if(seed==7)seed=0; else seed++;
	heap2clr = color[seed];
	if(seed==7)seed=0; else seed++;		
	heap3clr = color[seed];
	if(seed==7)seed=0; else seed++;
	heap4clr = color[seed];
	if(seed==7)seed=0; else seed++;
	heap5clr = color[seed];
			
			video_text(5, 5, "Please Press 1 to play against the computer OR 2 to play against a friend");
			video_text(29, 10, "First to 5 points wins!");
			video_text(20,20,"Player 1:");
			video_text(50,20,"Player 2 / Computer:");
			if(firstPlayerCounter == 0){
			    firstPlayerScore = "0";
			}else if(firstPlayerCounter == 1){
			    firstPlayerScore = "1";
			}else if(firstPlayerCounter == 2){
			    firstPlayerScore = "2";
			}else if(firstPlayerCounter == 3){
			    firstPlayerScore = "3";
			}if(firstPlayerCounter == 4){
			    firstPlayerScore = "4";
			}else if(firstPlayerCounter == 5){
			    firstPlayerScore = "5";
			} else if(firstPlayerCounter != 0 && firstPlayerCounter != 1 && firstPlayerCounter != 2 && firstPlayerCounter != 3 && firstPlayerCounter != 4 && firstPlayerCounter != 5){
			    firstPlayerScore = "0";
			    secondPlayerScore = "0";
			    firstPlayerCounter = 0;
			    secondPlayerCounter = 0;
			}
			
        if(secondPlayerCounter == 0){
			    secondPlayerScore = "0";
			}else if(secondPlayerCounter == 1){
			    secondPlayerScore = "1";
			}
			if(secondPlayerCounter == 2){
			    secondPlayerScore = "2";
			}else if(secondPlayerCounter == 3){
			    secondPlayerScore = "3";
			}if(secondPlayerCounter == 4){
			    secondPlayerScore = "4";
			}else if(secondPlayerCounter == 5){
			    secondPlayerScore = "5";
			} else if (secondPlayerCounter != 0 && secondPlayerCounter != 1 && secondPlayerCounter != 2 && secondPlayerCounter != 3 && secondPlayerCounter != 4 && secondPlayerCounter != 5){
			    secondPlayerCounter = 0;
			    secondPlayerScore = "0";
			    firstPlayerScore = "0";
			    firstPlayerCounter = 0;
			}
			video_text(25,27, firstPlayerScore);
			video_text(55,27, secondPlayerScore);
			int keyPressed;
			keyPressed = keyBoardInput();
			if(keyPressed == -1){
				introScreen = false;
				clear_char();
			}else if(keyPressed == 1){
				aiMode = true;
				twoPlayerMode = false;
				introScreen = false;
				clear_char();
			}else if(keyPressed == 2){
				twoPlayerMode = true;
				aiMode = false;
				introScreen = false;
				clear_char();
			}	

		}
		
		switch(numHeaps){
			case(1):{
				heap1x = RESOLUTION_X/2;
				heap2x = -1;
				heap3x = -1;
				heap4x = -1;
				heap5x = -1;
				break;
			}
			case(2):{
				heap1x = RESOLUTION_X/3;
				heap2x = 2 * heap1x;
				heap3x = -1;
				heap4x = -1;
				heap5x = -1;
				break;
			}
			case(3):{
				heap1x = RESOLUTION_X/4;
				heap2x = heap1x * 2;
				heap3x = heap1x * 3;
				heap4x = -1;
				heap5x = -1;
				break;
			}
			case(4):{
				heap1x = RESOLUTION_X/5;
				heap2x = heap1x * 2;
				heap3x = heap1x * 3;
				heap4x = heap1x * 4;
				heap5x = -1;
				break;
			}
			case(5):{
				heap1x = RESOLUTION_X/6;
				heap2x = heap1x * 2;
				heap3x = heap1x * 3;
				heap4x = heap1x * 4;
				heap5x = heap1x * 5;
				break;
			}
		default:{
		}
			
	}
		if(twoPlayerMode){
		
		/* Erase any boxes and lines that were drawn in the last iteration */
        clear_screen();
		
		
		draw_heap(heap1x, heap1, 7, heap1clr);  // draw first column
		draw_heap(heap2x, heap2, 7, heap2clr);  // draw second column
		draw_heap(heap3x, heap3, 7, heap3clr);  // draw third column
		draw_heap(heap4x, heap4, 7, heap4clr); // draw fourth column
		draw_heap(heap5x, heap5, 7, heap5clr); // draw fifth column
		
		video_text(15, 5, "The Game of NIM");

		
        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
		
		   
		
		if(d){
			playerNum = 1;
			video_text(50,5,"Player 1's turn"); // display that it's player 1's turn
		}else{
		    video_text(50,5,"Player 2's turn"); // display that its player 2's turn
			playerNum = 2;
		}
			
	    //printf("heap1:%d, heap2:%d, heap3:%d, heap4:%d, heap5:%d\n", heap1,heap2,heap3,heap4,heap5);
		
		if(heap1 == -1 && heap2 == -1 && heap3 == -1 && heap4 == -1 && heap5 == -1){
			d = !d; 
			if(d){
			playerNum = 1; // check if player 1 was the last play
		}else{
			playerNum = 2; // check if player 2 was the last play
		}
			printf("Player %d Wins!\n", playerNum);
	
                    	 heap1x = -1;
                    	 heap2x = -1;
                    	 heap3x = -1;
                    	 heap4x = -1;
	                    heap5x = -1;
						if(d){
						    firstPlayerCounter = 1 + firstPlayerCounter; // update score
						}else{
						    secondPlayerCounter = 1 + secondPlayerCounter; // update score
						}
						introScreen = true;
                        d = true;
						clear_char();
		}else{
			
		printf("Player %d: Which column would you like to remove pieces from? \n ", playerNum);
        colNum = keyBoardInput();
		
		printf("How many pieces would you like to remove from this column?\n");
		numPieces = keyBoardInput();
		
		bool inputError = false;	
		switch(colNum){
			case 1:{
				if (heap1>= numPieces) {heap1 -= numPieces;} else {printf("Not enough pieces in that column!\n");  inputError = true;}
				
				if (heap1 == 0){
					numHeaps--;	
					//heap 2 becomes heap 1
					//heap 3 becomes heap 2
					//heap 4 becomes heap 3
					//heap 5 becomes heap 4
					heap1 = heap2;
					heap1clr = heap2clr;
					heap2 = heap3;
					heap2clr = heap3clr;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
					
				}
				if(!inputError){d = !d;}
				break;
			}

			case 2:{
				if (heap2>= numPieces) {heap2 -= numPieces;} else {printf("Not enough pieces in that column!\n");  inputError = true;}
				if (heap2 == 0){
					numHeaps--;
					heap2 = heap3;
					heap2clr = heap3clr;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			}
			case 3:{
				if (heap3>= numPieces) {heap3 -= numPieces;}  else {printf("Not enough pieces in that column!\n");  inputError = true;}

				if (heap3 == 0){
					numHeaps--;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			}
			case 4:{
				if (heap4>= numPieces) {heap4 -= numPieces;} else {printf("Not enough pieces in that column!\n");  inputError = true;}

				if (heap4 == 0){
					numHeaps--;	
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			}
			case 5:{
				if (heap5>= numPieces) {heap5 -= numPieces;} else {printf("Not enough pieces in that column!\n");  inputError = true;}

				if (heap5 == 0){
					numHeaps--;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			 }
			default:
				break;
		     }
		 }	
        }else if(aiMode){
		
		/* Erase any boxes and lines that were drawn in the last iteration */
                clear_screen();
				clear_char();
		
		
		draw_heap(heap1x, heap1, 7, heap1clr);
		draw_heap(heap2x, heap2, 7, heap2clr);
		draw_heap(heap3x, heap3, 7, heap3clr);
		draw_heap(heap4x, heap4, 7, heap4clr);
		draw_heap(heap5x, heap5, 7, heap5clr);
		
		video_text(15, 5, "The Game of NIM");

		
                wait_for_vsync(); // swap front and back buffers on VGA vertical sync
                pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
		
		char* player;   
		
		if(d){
			player = "Player 1";
		}else{
			player = "Computer";
		}
			
	    printf("heap1:%d, heap2:%d, heap3:%d, heap4:%d, heap5:%d\n", heap1,heap2,heap3,heap4,heap5);
		
		if(heap1 == -1 && heap2 == -1 && heap3 == -1 && heap4 == -1 && heap5 == -1){
			
					
						d=!d;
			
						if(d){
							printf("Player 1 Wins!");
						}else{ printf("Computer Wins!");}
						heap1 = 1;
                    	heap2 = 3;
                    	heap3 = 5;
                    	heap4 = 7;
                    	heap5 = 9;
	
                    	 heap1x = -1;
                    	 heap2x = -1;
                    	 heap3x = -1;
                    	 heap4x = -1;
	                 	 heap5x = -1;
						
						numHeaps = 5;

						if(d){
						    firstPlayerCounter = 1 + firstPlayerCounter;
						}else{
						    secondPlayerCounter = 1 + secondPlayerCounter;
						}
						introScreen = true;
                                                d = true;
						clear_char();
		}else{
			
		if(d){
			    video_text(50,5,"Your Turn!");
                printf("Player: Which column would you like to remove pieces from? \n ");
                colNum = keyBoardInput();
			
				

                printf("How many pieces would you like to remove from this column?\n");
		numPieces = keyBoardInput();
			bool inputError = false;
                switch(colNum){
			case 1:{
				if (heap1>= numPieces) heap1 -= numPieces; else {printf("Not enough pieces in that column!\n");  inputError = true;}
				
				if (heap1 == 0){
					numHeaps--;	
					//heap 2 becomes heap 1
					//heap 3 becomes heap 2
					//heap 4 becomes heap 3
					//heap 5 becomes heap 4
					heap1 = heap2;
					heap1clr = heap2clr;
					heap2 = heap3;
					heap2clr = heap3clr;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
					
				}
				if(!inputError){d = !d;}
				break;
			}

			case 2:{
				if (heap2>= numPieces) heap2 -= numPieces; else {printf("Not enough pieces in that column!\n");  inputError = true;}
				if (heap2 == 0){
					numHeaps--;
					heap2 = heap3;
					heap2clr = heap3clr;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			}
			case 3:{
				if (heap3>= numPieces) heap3 -= numPieces; else {printf("Not enough pieces in that column!\n");  inputError = true;}

				if (heap3 == 0){
					numHeaps--;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			}
			case 4:{
				if (heap4>= numPieces) heap4 -= numPieces; else {printf("Not enough pieces in that column!\n");  inputError = true;}

				if (heap4 == 0){
					numHeaps--;	
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			}
			case 5:{
				if (heap5>= numPieces) heap5 -= numPieces; else {printf("Not enough pieces in that column!\n");  inputError = true;}

				if (heap5 == 0){
					numHeaps--;
					heap5 = -1;
				}
				if(!inputError){d = !d;}
				break;
			 }
			default:
				break;
		     }
                }else if (!d){
                //make computer move
                printf("Computer made its move; your turn!\n");
                int moveIndex = 1;
                int amount_to_remove = 1;
                int eights=0;int fours=0; int twos =0 ; int ones = 0;
                int col1=heap1;
                int col2=heap2;
                int col3=heap3;
                int col4=heap4;
                int col5=heap5;
                for(int i = 8; i>=1; i = i/2){
                    if(col1>=i){
                        col1 -= i;
                        switch(i){
                            case 8:{
                                eights++;
                                break;
                            }
                            case 4:{
                                fours++;
                                break;
                            }
                            case 2:{
                                twos++;
                                break;
                            }
                            case 1:{
                                ones++;
                                break;
                            }
                            default:
                                break;
                        }
                    }
					if(col2>=i){
                        col2 -= i;
                        switch(i){
                            case 8:{
                                eights++;
                                break;
                            }
                            case 4:{
                                fours++;
                                break;
                            }
                            case 2:{
                                twos++;
                                break;
                            }
                            case 1:{
                                ones++;
                                break;
                            }
                            default:
                                break;
                        }
                    }
					if(col3>=i){
                        col3 -= i;
                        switch(i){
                            case 8:{
                                eights++;
                                break;
                            }
                            case 4:{
                                fours++;
                                break;
                            }
                            case 2:{
                                twos++;
                                break;
                            }
                            case 1:{
                                ones++;
                                break;
                            }
                            default:
                                break;
                        }
                    }
					if(col4>=i){
                        col4 -= i;
                        switch(i){
                            case 8:{
                                eights++;
                                break;
                            }
                            case 4:{
                                fours++;
                                break;
                            }
                            case 2:{
                                twos++;
                                break;
                            }
                            case 1:{
                                ones++;
                                break;
                            }
                            default:
                                break;
                        }
                    }
					if(col5>=i){
                        col5 -= i;
                        switch(i){
                            case 8:{
                                eights++;
                                break;
                            }
                            case 4:{
                                fours++;
                                break;
                            }
                            case 2:{
                                twos++;
                                break;
                            }
                            case 1:{
                                ones++;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
                int nimSum = 8*(eights%2) + 4*(fours%2) + 2*(twos%2) + (ones%2);
                printf("NIMSUM is %d\n", nimSum);
				
                if(heap1 > 0){
                    int target_size1 = heap1 ^ nimSum;
                    if(target_size1 < heap1){
                        amount_to_remove = heap1 - target_size1;
                        moveIndex = 1;
                    }
                }
                if(heap2 > 0){
                    int target_size2 = heap2 ^ nimSum;
                    if(target_size2 < heap2){
                        amount_to_remove = heap2 - target_size2;
                        moveIndex = 2;
                    }
                }
                if(heap3 > 0){
                    int target_size3 = heap3 ^ nimSum;
                    if(target_size3 < heap3){
                        amount_to_remove = heap3 - target_size3;
                        moveIndex = 3;
                    }
                }
                if(heap4 > 0){
                    int target_size4 = heap4 ^ nimSum;
                    if(target_size4 < heap4){
                        amount_to_remove = heap4 - target_size4;
                        moveIndex = 4;
                    }
                }
                if(heap5 > 0){
                    int target_size5 = heap5 ^ nimSum;
                    if(target_size5 < heap5){
                        amount_to_remove = heap5 - target_size5;
                        moveIndex = 5;
                    }
                }

switch(moveIndex){
			case 1:{
				if (heap1>= amount_to_remove) heap1 -= amount_to_remove;
				
				if (heap1 == 0){
					numHeaps--;	
					//heap 2 becomes heap 1
					//heap 3 becomes heap 2
					//heap 4 becomes heap 3
					//heap 5 becomes heap 4
					heap1 = heap2;
					heap1clr = heap2clr;
					heap2 = heap3;
					heap2clr = heap3clr;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
					
				}
				d = !d;
				break;
			}

			case 2:{
				if (heap2>= amount_to_remove) heap2 -= amount_to_remove; 
				if (heap2 == 0){
					numHeaps--;
					heap2 = heap3;
					heap2clr = heap3clr;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				d = !d;
				break;
			}
			case 3:{
				if (heap3>= amount_to_remove) heap3 -= amount_to_remove;

				if (heap3 == 0){
					numHeaps--;
					heap3 = heap4;
					heap3clr = heap4clr;
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				d = !d;
				break;
			}
			case 4:{
				if (heap4>= amount_to_remove) heap4 -= amount_to_remove;

				if (heap4 == 0){
					numHeaps--;	
					heap4 = heap5;
					heap4clr = heap5clr;
					heap5 = -1;
				}
				d = !d;
				break;
			}
			case 5:{
				if (heap5>= amount_to_remove) heap5 -= amount_to_remove;

				if (heap5 == 0){
					numHeaps--;
					heap5 = -1;
				}
				d = !d;
				break;
			 }
			default:
				d = !d;
				break;
		     }
                }
		
		 }
		    
		}
	}
}



// code for subroutines


/* draws a heap */
void draw_heap(int heapX, int numBeads, int rad, short int clr){
	
	if(heapX > 0){
		short int color[] = {WHITE, YELLOW, RED, PINK, BLUE, CYAN, MAGENTA, GREEN, ORANGE};
		for(int i=0; i<numBeads; i++){
			draw_bead(heapX, 50+(i*(2*rad+5)), rad, clr);//color[rand() % 9]);
		}
	}
}

/* draw a circle */
void draw_bead(int x, int y, int r, short int clr){
        	int r2 = r * r;
			int area = r2 << 2;
			int rr = r << 1;

			for (int i = 0; i < area; i++){
    			int tx = (i % rr) - r;
    			int ty = (i / rr) - r;

    			if (tx * tx + ty * ty <= r2)
        		plot_pixel(x + tx, y + ty, clr);
			}
		}

void video_text(int x, int y, char * text_ptr) {
	int offset;
	volatile char * character_buffer = (char*)0xC9000000;
	offset = (y << 7) + x;
	while (*(text_ptr)) {
		*(character_buffer + offset) = *(text_ptr); // write to the character buffer
		++text_ptr;
		++offset;
	}


}

void wait_for_vsync(){
	volatile int * pixel_ctrl_ptr = 0xFF203020;
	register int status;
	
	*pixel_ctrl_ptr = 1; //start the synchronization process
	
	status = *(pixel_ctrl_ptr + 3);
	while((status & 0x01) != 0){
		status = *(pixel_ctrl_ptr + 3);
	}
}

void clear_screen(){
	for(int i=0; i<RESOLUTION_X; i++){
		for(int j=0; j<RESOLUTION_Y; j++){
			plot_pixel(i, j, 0);
		}
	}
}

void plot_pixel(int x, int y, short int line_color){
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

int keyBoardInput() {
  /* Declare volatile pointers to I/O registers (volatile means that IO load
  and store instructions will be used to access these pointer locations,
  instead of regular memory loads and stores) */
  volatile int * PS2_ptr = (int * ) 0xFF200100;
  int PS2_data, RVALID;
  char byte1 = 0, byte2 = 0, byte3 = 0;
  // PS/2 mouse needs to be reset (must be already plugged in)
  *(PS2_ptr) = 0xFF; // reset

  int matchedCode;
  bool inputFinished = false;
  while (!inputFinished) {
    PS2_data = * (PS2_ptr); // read the Data register in the PS/2 port
    RVALID = PS2_data & 0x8000; // extract the RVALID field

    if (RVALID) {
      /* shift the next data byte into the display */
      byte1 = byte2;
      byte2 = byte3;
      byte3 = PS2_data & 0xFF;
      if ((byte2 == (char) 0xAA) && (byte3 == (char) 0x00))
        // mouse inserted; initialize sending of data
        *
        (PS2_ptr) = 0xF4;
      unsigned int shift_buffer[3];
      shift_buffer[2] = byte3;
      shift_buffer[1] = byte2;
      shift_buffer[0] = byte1;

      if (shift_buffer[0] == 90 && shift_buffer[1] == 240 && shift_buffer[2] == 90) //Enter hit
        inputFinished = true;
      else if (shift_buffer[2] != 240 && shift_buffer[2] != 90)
        matchedCode = shift_buffer[2];
    }
  }
  switch (matchedCode) { 
  case 69:
    return 0;
  case 22:
    return 1;
  case 30:
    return 2;
  case 38:
    return 3;
  case 37:
    return 4;
  case 46:
    return 5;
  case 54:
    return 6;
  case 61:
    return 7;
  case 62:
    return 8;
  case 70:
    return 9;
  case 90:
    return 250;
  case 240:
    return 251;
  default: //non-number key
    return -1;
  }
}

clear_char()
{
	for(int x=0; x<=79;x++)
	{
		for(int y=0;y<=59;y++)
		video_text(x,y," ");
	}
}



	
	
	
	
	
	
	
	

