/**
* Title: all_pairs.cpp
* Abstract: This program implements the Floyd's algorithm to display
*			all-pairs shortest paths of an adjacent matrix. First, your
*			program should ask a user for a text file name to read a 2-D
*			array of a sequence of numbers. Then, it should display all
*			intermediate and final results for the input matrix.
*			- maximum input matrix is less than or equal to 11-by-11
*			- the matrix uses -1 to indicate infinity
* Author: Eduardo Trejo
* ID: 6787
* Date: 5/1/2015
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
using namespace std;

static int vertices;
const int MAX_AMOUNT = 11;

int main()
{
	int fileContent[MAX_AMOUNT][MAX_AMOUNT][MAX_AMOUNT];
	ifstream myfile;
	string file, line;

	cout << "Enter a file name: ";
	cin >> file;

	myfile.open(file.c_str());
	myfile >> vertices;

	if (myfile.fail())
	{
		cout << "File does not exist." << endl;
		exit(1);
	}

	// Set -1 to 999, to test for min.
	for (int a = 1; a <= vertices; a++)
	{
		for (int b = 1; b <= vertices; b++)
		{
			myfile >> fileContent[0][a][b];
			if (fileContent[0][a][b] == -1)
			{
				fileContent[0][a][b] = 999;
			}
		}
	}

	// Floyd Algorithm.
	for (int k = 1; k <= vertices; k++)
	{
		for (int i = 1; i <= vertices; i++)
		{
			for (int j = 1; j <= vertices; j++)
			{
				fileContent[k][i][j] = min(fileContent[k - 1][i][j], fileContent[k - 1][i][k] + fileContent[k - 1][k][j]);
			}
		}
	}

	// Print out all the pairs, changes.
	for (int k = 0; k <= vertices; k++)
	{
		cout << "D[" << k << "]:";

		for (int i = 1; i <= vertices; i++)
		{
			for (int j = 1; j <= vertices; j++)
			{
				if (fileContent[k][i][j] == 999)
				{
					cout << "	" << setw(2) << -1 << " ";
				}
				else
				{
					cout << "	" << setw(2) << fileContent[k][i][j] << " ";
				}
			}
			cout << "\n";
		}
		cout << endl;
	}

	myfile.close();

	return 0;
}