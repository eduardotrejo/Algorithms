/**
* Title: coin_collection.cpp
* Abstract: The program's use is to collect the maximum number of coins on
*			an n x m board. First, the program will ask a user for a text file
*			name to read a 2-D array of a sequence of numbers. In the array,
*			one indicates that there's a coin on the cell, while zero means no
*			coin. After that the program will display maximum number of coins and
*			path to collect them. If it is possible more that two possible paths
*			displaying one of them is good enough.
*			- Board size is less than or equal to 50 x 50.
* Author: Eduardo Trejo
* Date: 4/24/2015
*/

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int R_MAX = 50;
const int C_MAX = 50;
const int MAX_IN = 250;

int main()
{
	ifstream myfile;
	string file, line;
	int content, row = 0, col = 0;
	int collector[R_MAX][C_MAX];
	int collectorCount[R_MAX][C_MAX];
	string storage[MAX_IN];

	cout << "Please enter a file name: ";
	cin >> file;

	myfile.open(file.c_str());
	if (myfile.fail())
	{
		cout << "File does not exist." << endl;
		exit(1);
	}

	// Counts the number of rows and colums and inputs
	// the content into the array.
	while (getline(myfile, line))
	{
		istringstream stream(line);
		col = 0;
		while (stream >> content)
		{
			collector[row][col] = content;
			col++;
		}
		row++;
	}

	// Dynamic programming algorithm.
	collectorCount[0][0] = collector[0][0];

	for (int j = 1; j < col; j++)
	{
		collectorCount[0][j] = collectorCount[0][j - 1] + collector[0][j];
	}

	for (int i = 1; i <= row; i++)
	{
		collectorCount[i][0] = collectorCount[i - 1][0] + collector[i][0];

		for (int j = 1; j < col; j++)
		{
			collectorCount[i][j] = max(collectorCount[i - 1][j], collectorCount[i][j - 1]) + collector[i][j];
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << collectorCount[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Max coins: " << collectorCount[row - 1][col - 1] << endl;
	int row2 = row - 1;
	int col2 = col - 1;
	int count = 0;

	cout << "Path: (1,1)->";
	stringstream firstConvert, secondConvert;
	string firstResult, secondResult;
	firstConvert << row;
	firstConvert >> firstResult;
	secondConvert << col;
	secondConvert >> secondResult;
	storage[count] = firstResult + "," + secondResult;
	count++;
	while (row2 > 0 && col2 > 0)
	{
		/*if (row2 == 0 && col2 == 0)
		{
		break;
		}*/
		if (collectorCount[row2 - 1][col2] > collectorCount[row2][col2 - 1])
		{
			row2--;
			stringstream converter, converter2;
			string result, result2;
			converter << row2 + 1;
			converter >> result;
			converter2 << col2 + 1;
			converter2 >> result2;
			storage[count] = result + "," + result2;
		}
		else
		{
			col2--;
			stringstream converter, converter2;
			string result, result2;
			converter << row2 + 1;
			converter >> result;
			converter2 << col2 + 1;
			converter2 >> result2;
			storage[count] = result + "," + result2;
		}
		count++;
	}

	for (int i = count - 1; i >= 0; i--)
	{
		cout << "(" << storage[i] << ")";
		if (i > 0)
		{
			cout << "->";
		}
	}
	cout << endl;
	myfile.close();

	return 0;
}
