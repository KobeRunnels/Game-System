#pragma comment(lib, "winmm.lib") 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15
#define G 16

typedef int bool;
#define true 1
#define false 0

void preEnter()
{
	int in;
	printf("\nPress Enter");
	while(in != 13)
	{
		in = getch();
	}
}

int pause(double he) // pauses for he number of seconds
{
    time_t then;
    
    time(&then);
    while(difftime(time(NULL),then) < he);
    fflush(stdin); // clears any extra enter presses
}

void setCursor(int x, int y) // sets cursor to a position on the screen
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD p = {x,y};
    SetConsoleCursorPosition(h,p);
}

void printAt(char c, int x, int y) // prints a character at an x and y location on the screen
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD p = {x,y};
    SetConsoleCursorPosition(h,p);
    putchar(c);
}

/* Colors
	1-Dark Blue
	2-Green
	3-Light-ish Blue
	4-Red
	5-Purple
	6-Dark Yellow
	7-Gray
	8-Dark Gray
	9-Light Blue
	A-Light Green
	B-Sky Blue
	C-Light Red
	D-Light Purple
	E-Yellow
	F-White
	G-Black

*/

void setColor(int ForgC) // sets color for text
{
	 WORD wColor;
	
	  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);	
	  CONSOLE_SCREEN_BUFFER_INFO csbi;
	
 	                      //We use csbi for the wAttributes word.
 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 	{
 	                //Mask out all but the background attribute, and add in the forgournd color
 	     wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F); // 0xF0 is red
 	     SetConsoleTextAttribute(hStdOut, wColor);
 	}
 	return;
}

int giveChoices(char * choiceA, char * choiceB,char * choiceC,char * choiceD, int x,int y) // creates decision menu between at the most four strings
{
	int decision = 1;
	int input = 0; // clears input to 0 because for some reason later on I had an issue where the keyboard would process 13 from the start
	int arrowX = x-1;
	int arrowY = y;
	int loopy; // used to clear arrows
	int choices = 0;
	
	// checks if decisions are not blank strings
	bool decision1 = true;
	bool decision2 = true;
	bool decision3 = true;
	bool decision4 = true;

	if(strcmp("",choiceA) == 0)
		decision1 = false;
	else
		choices++;	
	
	if(strcmp("",choiceB) == 0)
		decision2 = false;
	else
		choices++;	
	
	if(strcmp("",choiceC) == 0)
		decision3 = false;
	else
		choices++;	
	
	if(strcmp("",choiceD) == 0)
		decision4 = false;
	else
		choices++;	
	
	
	for(loopy = 0;loopy<4;loopy++) // clears extra arrows if the player tries to use escape in a loop
	{
		printAt(' ',arrowX,arrowY+loopy);
	}
	while(input!=13 && input != 27)
	{
		setCursor(x,y);
		printf("%s",choiceA);
		setCursor(x,y+1);
		printf("%s",choiceB);
		setCursor(x,y+2);
		printf("%s",choiceC);
		setCursor(x,y+3);
		printf("%s",choiceD);
		printAt('>',arrowX,arrowY);
		input = getch();
		if(input == 27)
			return 27;
		switch(input)
		{
			case 72:
			decision--;
			if(decision<1)
			{
				decision++;
			}
			break;
			case 80:
			decision++;
			if(decision>choices)
			{
				decision--;
			}
			break;
		}
		printAt(' ',arrowX,arrowY);
		switch(decision)
		{
			case 1:
			arrowY = y;
			break;
			case 2:
			arrowY = y+1;
			break;
			case 3:
			arrowY = y+2;
			break;
			case 4:
			arrowY = y+3;
			break;
		}
	}
	
	setCursor(x,y+5);
	return decision;
}

int valueSlider(char question[30], int min, int max,int x,int y) // for picking a value
{
	int input;
	int value = min;
	while(input!=13 && input != 27)
	{
		setCursor(x,y);
		printf("%s",question);
		setCursor(x,y+1);
		printf("%d",value);
		input = getch();
		switch(input)
		{
			case 75: // left
			if(value != min)
				value--;
			break;
			case 77: // right
			if(value != max)
				value++;
			break;
		}
	}
	if(input == 13)
		return value;
	return 0;
}

void hideCursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

