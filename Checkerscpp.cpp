#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <Windows.h>
#include "MMSystem.h"
using namespace std;

class game
{
public:
	void mainLine();

private:
	void init(void);
	void gameMenu(void);
	void eoj(void);
	void displayMenu(void);
	int menuPic(void);
	void startGameOver(void);
	void displayBoard(void);
	void placePieces(void);
	void makeAJump();
	void playerW_move(void);
	void playerB_move(void);
	void checkWinner(void);
	void checkGameOver(void);
	void writeStatsDataFile(string);
	
	int playerTurn;
	string cBoard[8][8];
	int row;
	int col;
	bool endFlag;
	string gameResults;
	long clockTick;
	string currentActionTaken;//may not need in checkers
	int row1, row2, col1, col2;
	string holdChar;
	string player1 = "B";
	string player2 = "W";
	char draw;
	int count1;
	int count2;
};
void main(void)
{
	game g1;
	g1.mainLine();

	system("pause");
}
void game::mainLine(void)
{
	init();

	while (endFlag == false)
	{
		gameMenu();
	}

	eoj();
}
void game::init(void)
{
	clockTick = time(0);

	// Load boardTable for game to start.
	
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				if (((x + y + 1) % 2) == 0)
				{
					cBoard[y][x] = ' ';
				}
				else if (((x + y + 1) % 2) == 1)
				{
					cBoard[y][x] = ' ';
				}

			}
		}
	}

	// Setup other start items.
	endFlag = false;
	gameResults = "No game results yet.";
	playerTurn = 1;
	
	placePieces();
	// Like a priming for the game.
	displayBoard();
	gameMenu();
}

void game::placePieces(void)
{

	
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (((x + y) % 2) == 0)
			{
				cBoard[y][x] = player1;
			}
		}
	}

	for (int y = 5; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (((x + y) % 2) == 0)
			{
				cBoard[y][x] = player2;
			}
		}
	}

}
void game::gameMenu(void)
{
	int aPic = 1;
	displayMenu();
	aPic = menuPic();
	
	switch (aPic)
	{

		// Start the game over.
	case 1:
		startGameOver();
		currentActionTaken = "Start the game over.";
		cout << currentActionTaken << endl;
		writeStatsDataFile("Starting the game over.");
		break;
	case 2:
		if (playerTurn % 2==0)
		{
			playerW_move();
			writeStatsDataFile("Make a move player White.");
		}
		else
		{
			playerB_move();
			writeStatsDataFile("Make a move player Black.");
		}
		break;
	case 3:
		displayBoard();
		writeStatsDataFile("Display the Board.");
		break;
	case 4:
		checkWinner();
		gameResults = draw;
			cout << "Its a draw.\n";
		writeStatsDataFile("Check for a Winner.");
		
		break;
	case 5:
		checkGameOver();
		writeStatsDataFile("Check for end of game.");
		break;
	case 6:
		endFlag = true;
		break;

	default:
		cout << "No option picked." << endl;

	}
}

void game::eoj(void)
{
	cout << "The results of the game: " << gameResults << endl;
	checkWinner();
	
	{
		gameResults = draw;
		cout << "Its a draw.\n";
	}
		
	cout << endl << "Game Over" << endl;
	writeStatsDataFile("Game is now ENDING.");

	
}
void game::displayMenu(void)
{
	cout << endl;
	cout << "The Checkers Game" << endl;
	cout << "FIRST PLAYER TO GO IS BLACK!!"<< endl;
	cout << "Menu Options" << endl;
	cout << "*************************" << endl;
	cout << "1) Start a new game." << endl;
	cout << "2) Make a move." << endl;
	cout << "3) Show the current Checker Board." << endl;
	cout << "4) Check for a Winner." << endl;
	cout << "5) Check for Game Over Status." << endl;
	cout << "6) End the game." << endl;
	cout << endl;
	cout << "Make your selection and press enter: " << endl;

}
void game::startGameOver(void)
{
	// Load boardTable for game to start.
	{
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				if (((x + y + 1) % 2) == 0)
				{
					cBoard[y][x] = ' ';
				}
				else if (((x + y + 1) % 2) == 1)
				{
					cBoard[y][x] = ' ';
				}

			}
		}
	}

	// Setup other start items.
	endFlag = false;
	
	gameResults = "No game results yet.";
	placePieces();
	// Like a priming for the game.
	displayBoard();
	displayMenu();

}

int game::menuPic(void)
{
	int pick;

	cin >> pick;

	system("cls");

	return pick;
}



void game::displayBoard(void)
{

	long howLong;

	howLong = time(0) - clockTick;

	cout << "The computer clock is at this many seconds: " << clockTick << endl;
	cout << "The game has been running for this many seconds: " << howLong << endl << endl;

	cout << "  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n";
	cout << "-----------------------------------\n";

	for (int y = 0; y < 8; y++)
	{
		static int x = 0;
		cout << y + 1 << " | ";
		for (int x = 0; x < 8; x++)
		{
			cout << cBoard[y][x] << " | ";
		}
		cout << endl << "-----------------------------------" << endl;
	}
}

void game::makeAJump()
{
	

	
}


void game::playerW_move(void)
{
	displayBoard();
	cout << "Lets get the coordinates of the piece you are moving." << endl;
	cout << "What is the row number of the piece you are moving?" << endl;
	cin >> row1;
	cout << "What is the column number of the piece you are moving?" << endl;
	cin >> col1;
	cout << "Now lets get the coordinates of the spot you wish to move to." << endl;
	cout << "What is the row number of the spot you wish to move to?" << endl;
	cin >> row2;
	cout << "What is the column number of the spot you wish to move to?" << endl;
	cin >> col2;

	holdChar = cBoard[row1 - 1][col1 - 1];
	cBoard[row1 - 1][col1 - 1] = " ";

	cBoard[row2 - 1][col2 - 1] = holdChar;

	checkWinner();

	playerTurn + 1;
	
}

void game::playerB_move(void)
{
	displayBoard();
	cout << "Lets get the coordinates of the piece you are moving." << endl;
	cout << "What is the row number of the piece you are moving?" << endl;
	cin >> row1;
	cout << "What is the column number of the piece you are moving?" << endl;
	cin >> col1;
	cout << "Now lets get the coordinates of the spot you wish to move to." << endl;
	cout << "What is the row number of the spot you wish to move to?" << endl;
	cin >> row2;
	cout << "What is the column number of the spot you wish to move to?" << endl;
	cin >> col2;

	holdChar = cBoard[row1 - 1][col1 - 1];
	cBoard[row1 - 1][col1 - 1] = " ";

	cBoard[row2 - 1][col2 - 1] = holdChar;

	checkWinner();
	
	playerTurn + 1;
}

void game::checkWinner(void)
{
	count1 = 0;
	count2 = 0;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (cBoard[x][y] == player1)
			count1++;
		}
	}
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (cBoard[x][y]== player2)
				count2++;
		}
	}
	{
		if (count2 = 0)
			gameResults = player1;
		
		else if (count1 = 0)
			gameResults = player2;

		else
			gameResults = draw;
	}
	{
		if (gameResults == player1)
			cout << "**********BLACK WINS!!************\n";
			
		
		else if (gameResults == player2)
			cout << "**********RED WINS!!**************\n";
		 
	}
}



void game::checkGameOver(void)
{
	endFlag = true;
}

/* *************************************************************** */
	// Use this module to write stat data to stat.txt data file
	// Open file first (use append to setup for adding records to existing file)
	// Write data to file
	// Close data file

void game::writeStatsDataFile(string dataItem)
{
	ofstream outFile;
	long currentTime;
	string sFileName;

	currentTime = time(0);

	sFileName = "statFile.txt";
	outFile.open(sFileName, ios::app);

	if (outFile.fail())
		cout << "Sequential file open failed" << endl;

	outFile << currentTime << "  " << dataItem;
	outFile << endl;

	outFile.close();



}

