MIT License

Copyright (c) [2024] [VICTOR]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


#include <iostream>
#include <conio.h>
#include <time.h> 
#include <windows.h>
using namespace std;

bool GameOver; //game over

const int width = 20; //width and height of the game
const int height = 20; //width and height of the game
int x, y, fruitX, fruitY, score; //head and fruit
int tailX[100], tailY[100]; //tail
int nTail; //tail length

enum eDirection { STOP = 0, LEFT, RIGHT, UP ,DOWN }; //direction
eDirection dir;//direction

void Setup() 
{
	GameOver = false;//game over
	dir = STOP;//direction
	x = width / 2;//head
	y = height / 2;//head
	fruitX = rand() % width;//random fruit
	fruitY = rand() % height;//random fruit
	score = 0;

}

void Draw()
{
	system("cls"); //system clear
	for (int i = 0; i < width+2; i++)//top wall
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) //height
	{
		for (int j = 0; j < width; j++)//width
		{

			if (j == 0)//left wall
				cout << "#";

			if (i == y && j == x)//head
				cout << "0";

			else if (i == fruitY && j == fruitX)//fruit
				cout << "O";

			else
			{
				
				for (int k = 0; k < nTail; k++)//tail
				{
					bool print = false;
					if (tailX[k] == j && tailY[k] == i)//tail
						cout << "0";
					    print = true;
					
					if (!print)//if no tail
						cout << " ";
				}
				
				cout << " ";
			}
			if (j == width - 1)
				cout << "#";

		}
		cout << endl;
	}


	for (int i = 0; i < width+2; i++) //bottom wall
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "Press x to quit the game" << endl;

}

void Input() //input from keyboard
{
	if (_kbhit()) //if keyboard hit
	{
		switch (_getch()) //get character
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			GameOver = true;
			break;

		}

	}

    if (x >= width) x = 0; else if (x < 0) x = width - 1; //if head hits the wall
	if (y >= height) y = 0; else if (y < 0) y = height - 1; //if head hits the wall

	for (int i = 0; i < nTail; i++) //if head hits the tail
		{
		if (tailX[i] == x && tailY[i] == y)
			GameOver = true;
	}
	if (x == fruitX && y == fruitY) //if head hits the fruit
	{

		score += 10;
		fruitX = rand() % width; //random fruit
		fruitY = rand() % height; //random fruit
		nTail++; //tail length

	}

}

void Logic()
{
	int prevX = tailX[0]; //tail
	int prevY = tailY[0]; //tail
	int prev2X, prev2Y; //tail
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) //tail

	{
		prev2X = tailX[i]; 
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
		

	}

    switch (dir) //direction
    {
		case LEFT:
            x--;
            break;
		case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default: //stop
            break;
    }


	
}

int main() {
	srand(time(NULL)); // random
	Setup(); //setup
	while (!GameOver) //game over
	{
		Draw(); //draw
		Input(); //input
		Logic(); //logic

		Sleep(10); 

	}

	return 0; 
}
