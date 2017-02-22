/**
* Title: knapsack.cpp
* Abstract: This program solves the Knapsack problem using dynamic programming.
*			The program reads in the weight and value of each item from a user
*			and determines the best subset.
* Author: Eduardo Trejo
* Date: 5/1/2015
*/

#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

const int MAX_ITEMS = 15;
const int MAX_CAPACITY = 15;
int matrix_design[MAX_ITEMS][MAX_CAPACITY];
int itemsSelected[MAX_ITEMS][MAX_CAPACITY];
int knapsack(int N, int W, int weight[], int value[]);

int main()
{
	int numberOfItems, capacity, inputValue, weightValue;
	int values[MAX_ITEMS];
	int weights[MAX_CAPACITY];

	// Initialize to 0.
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		for (int j = 0; j < MAX_CAPACITY; j++)
		{
			matrix_design[i][j] = 0;
		}
	}

	// Read in user input.
	cout << "Number of items: ";
	cin >> numberOfItems;

	cout << "Knapsack capacity: ";
	cin >> capacity;

	cout << "Enter the weights and values of " << numberOfItems << " items." << endl;

	for (int i = 0; i < numberOfItems; i++)
	{
		cout << "	Item " << i + 1 << ": ";
		cin >> weightValue >> inputValue;
		weights[i] = weightValue;
		values[i] = inputValue;
	}

	// Function call.
	knapsack(numberOfItems, capacity, weights, values);

	cout << "\ni|j:";
	// Column labels.
	for (int i = 0; i <= capacity; i++)
	{
		if (i == 0)
		{
			cout << "    " << setw(2) << i;
		}
		else
		{
			cout << "	" << setw(2) << i;
		}	
	}
	cout << endl;

	for (int i = 0; i <= numberOfItems; i++)
	{
		// Row Labels.
		cout << setw(2) << i << " :";
		for (int j = 0; j <= capacity; j++)
		{
			cout << "	" << setw(2) << matrix_design[i][j] << " ";
		}
		cout << endl;
	}

	int changeItems = numberOfItems;
	int capSize = capacity;

	// Prints out the index of the item that was selected.
	cout << "\nBest set: ";
	while (changeItems > 0)
	{
		if (itemsSelected[changeItems][capSize] == 1)
		{
			cout << changeItems << "  ";
			changeItems--;
			capSize -= weights[changeItems];
		}
		else
		{
			changeItems--;
		}
	}
	cout << "\nMax value: " << knapsack(numberOfItems, capacity, weights, values) << endl;
	return 0;
}

int knapsack(int N, int W, int weights[], int values[]){
	
	// First row will always be all 0's, meaning that no items are available.

	// Storing values into the matrix_design.
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j <= W; j++)
		{
			if (weights[i - 1] <= j)
			{
				matrix_design[i][j] = max(matrix_design[i - 1][j], values[i - 1] + matrix_design[i - 1][j - weights[i - 1]]);

				// Tracking if the item was selected as an optimal solution.
				if (values[i - 1] + matrix_design[i - 1][j - weights[i - 1]] > matrix_design[i - 1][j])
				{
					itemsSelected[i][j] = 1;
				}
				else
				{
					itemsSelected[i][j] = -1;
				}
			}
			else
			{
				matrix_design[i][j] = matrix_design[i - 1][j];
			}
		}
	}

	return  matrix_design[N][W];
}
