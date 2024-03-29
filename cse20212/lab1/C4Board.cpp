/* 
	John Lake C4Board.cpp
	Implementation for the C4Board class
*/
#include "C4Col.h"
#include "C4Board.h" 
#include <iostream> 
#include <cctype>
#include <cstdlib> 
#include <cstdio> 
using namespace std; 

//Default constructor
C4Board::C4Board(){
	numCols = 7; 		     //Default # of columns. 
	Board = new C4Col[numCols];  //Array of the column objects used in the game
}

//Deconstructor
C4Board::~C4Board(){
	delete[] Board; //Delete the column objects
}

//Displays the current board. 
void C4Board::display(){
	for(int i = Board[0].getMaxDiscs()-1; i>=0;i--){  //The loop will run from the top row to the bottom. 
		for(int j=0;j<numCols;j++){               //Goes from the left column to the right
			cout << "|"<< Board[j].getDisc(i)<<" "; //Print the contents of each cell between the '|' character
		}
		cout <<"|"<< endl; //At the end of each row, print a newline 
	}
}
//Allows 2 players to play the game. 
void C4Board::play(){
	int turn = 1;   	//variable used to determine the who should go on a given turn.  Player 1 goes first
	int gameLoop = 1;  	//Used to continue the loop that the game is played in.  When the game is over, this is set to zero
	int input; 		//This is the number the user enters to give a column #
 		
	printf("\033[2J\033[H"); //Clear screen
	while(gameLoop){
		display(); //Display the board.
		cout <<endl;  
		if(turn%2==1){					  						//P1's turn			
			cout <<"Which column would you like to put a disc? " << endl; 				//Prompt the user
			cout << "Enter the column #, from 1 to "<<numCols<<", or -1 to end the game. " << endl;
			cin >> input; 
			printf("\033[2J\033[H"); //Clear screen
			
			if (input == -1){ 	//If the user inputs -1, exit.
				 gameLoop = 0; 
			}
			else if (input>numCols || input <1){	//If they enter a number off of the board, other than -1, give an error message. 
				cout << "That is not a valid space on the board!!!"<<endl;
				turn++; 	//Player will go again
			}
			else{ //Input is appropriate: 
				if(Board[input-1].isFull()){ 
					//If the board is full, attempt to add the disc (gives error message), then let the user try again
					Board[input-1].addDisc('X'); 
					turn++;  
				}
				else{Board[input-1].addDisc('X');}// "input-1" is used because it is more natural to enter '1' for the first column.
			}
		
		}	
		else{ //It's player 2's turn (the computer)
			printf("\033[2J\033[H"); //Clear screen
			compTurn(); 
		}	
		switch(gameOver()){ //Checks if the game is over, and checks who won if it returns true.  
					case 1: 
						printf("\033[2J\033[H"); //Clear screen
						cout << "Player 1 wins! Congratulations!!!"<<endl; 
						gameLoop=0; 
						break; 
					case 2: 
						printf("\033[2J\033[H"); //Clear screen
						cout << "Player 2 wins! Congratulations!!!"<<endl; 
						gameLoop=0; 
						break; 
					case 0: 	
						turn++; //If the game isn't over, change the turn.  
						break; 
		}						
	} 
	display(); //Display the board.  (To show the final board to the user.) 
}

//Helper function that determins whether or not the game is over.  
//I check horizontally, vertically, and diagonally.  Each part moves from left to right, as it would be redundant to also check from the other side
int C4Board::gameOver(){
	int count1=0; int count2=0; //Count the number of plays by player 1 and player 2, respectively. 
	//Check to see if there are any 4-in-a-row plays
	
	//Horizontal: 
	for(int j=0;j<Board[0].getMaxDiscs();j++){  //j is the row
		for(int i=0;i<numCols-3;i++){  //i is the column
			for(int k=0;k<4;k++){   //Traverse to the right from the start point 4 spaces, including the start point
				if(Board[i+k].getDisc(j) == 'X'){count1++;count2=0;} 
				if(Board[i+k].getDisc(j) == 'O'){count2++;count1=0;}
				
				if(count1 >= 4 || count2 >=4){ //game's over
					return (count1>count2)? (1) : (2);  //Return the appropriate result
				}
			}
			count1=0; count2=0; 
		}
	}
	count1=0; count2=0; 
	
	//Vertical: 
	for(int i=0;i<numCols;i++){  //i is the column
		for(int j=0;j<Board[0].getMaxDiscs()-3;j++){  //j is the row
			for(int k=0;k<4;k++){ //Go up from the start point 3 spaces, and check each one.  
				if(Board[i].getDisc(j+k) == 'X'){count1++;count2=0;} 
				if(Board[i].getDisc(j+k) == 'O'){count2++;count1=0;}
				
				if(count1 >= 4 || count2 >=4){ //game's over
					return (count1>count2)? (1) : (2); 
				}
			}
			count1=0; count2=0; 
		}
	}
	count1=0; count2=0; 

	//Diagonal (Up and right) 
	for(int i=0;i<numCols-3;i++){  //i is the column
		for(int j=0;j<Board[0].getMaxDiscs()-3;j++){  //j is the row
			for(int k=0;k<4;k++){ //Go up and to the right 3 spaces
				if(Board[i+k].getDisc(j+k) == 'X'){count1++;count2=0;} 
				if(Board[i+k].getDisc(j+k) == 'O'){count2++;count1=0;}
				if(count1 >= 4 || count2 >=4){ //game's over
					return (count1>count2)? (1) : (2); 
				}
			}
			count1=0; count2=0; 
		}
	}
	count1=0; count2=0; 
	
	
	//Diagonal (Down and Right) 
	for(int i=0;i<numCols-3;i++){  //i is the column
		for(int j=Board[0].getMaxDiscs()-1;j>2;j--){  //j is the row
			for(int k=0;k<4;k++){  //Go down and to the right 3 spaces
				if(Board[i+k].getDisc(j-k) == 'X'){count1++;count2=0;} 
				if(Board[i+k].getDisc(j-k) == 'O'){count2++;count1=0;}
				if(count1 >= 4 || count2 >=4){ //game's over
					return (count1>count2)? (1) : (2); 
				}
			}
			count1=0; count2=0; 
		}
	}
	return 0;  //If nobody won, return 0
}


//Makes the computer take a turn
void C4Board::compTurn(){
	int done = 0; 
	while(!done){ //Keep trying columns until one is not full
		int i = rand()%7;  //try a random column
		if(!Board[i].isFull()){ //if it isn't full, add an O (P2 piece) to that column, and end the loop.  
			Board[i].addDisc('O'); 
			done=1; 
		}
	}
}


