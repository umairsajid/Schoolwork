/*
	John Lake C4Col.h
	Interface for the column class
*/

#ifndef C4COL_H
#define C4COL_H

class C4Col {
	public: 
		C4Col(); //Default constructor
		~C4Col(); //Deconstructor
		int isFull();      //Determines if numDiscs == maxDiscs
		char getDisc(int); //returns the specified disk from Discs[];
		int getMaxDiscs(); //returns maxDiscs
		int addDisc(char); //Adds a disc to the corresponding column. 
	private: 
		int numDiscs; //Number of discs in the column so far
		int maxDiscs; //Number of discs the column can hold (# of rows) 
		char * Discs; //Array that stores which player (X or O) has each spot 
};
#endif
