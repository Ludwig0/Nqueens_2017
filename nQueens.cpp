#include <iostream>
#include <vector>
using namespace std;

int nQueens(int n)
{
	int numOfSolutions = 0;

	//index+1 = y positions from top right
	int *queenPositions = new int[n];
	//used later for keeping track of used positions when backtracking, reset each time initial queen position
	bool *previouslyTried = new bool[n*n];
	for (int i = 0; i < n*n; i++)
	{
		*(previouslyTried + i) = false;
	}

	//initial position for queen on n size board
	for (int i = 0; i < n; i++)
	{

		*queenPositions = i;
		//resets previous tried each
		for (int i = 0; i < n*n; i++)
		{
			previouslyTried[i] = false;
		}

		bool isChecking = true;
		int row = 1;
		bool collumnAllowed;
		while (isChecking)
		{
			bool hasSpot = false;
			int collumn = 0;

			while (collumn < n && !hasSpot)
			{
				collumnAllowed = true;
				for (int queenNumber = 0; queenNumber < row; queenNumber++)
				{
					//will skip collumn if previous queen is in it
					if (queenPositions[queenNumber] == collumn)
						collumnAllowed = false;
					if ((queenPositions[queenNumber] + queenNumber) == (collumn + row) || (queenPositions[queenNumber] - queenNumber) == (collumn - row))
						collumnAllowed = false;
					if (previouslyTried[n*row + collumn])
						collumnAllowed = false;
				}
				if (collumnAllowed)
				{
					queenPositions[row] = collumn;
					previouslyTried[n*row + collumn] = true;
					hasSpot = true;
				}
				collumn++;
			}

			if (row == 0)
			{
				isChecking = false;
			}
			else if (row == n - 1 && collumnAllowed)
			{
				numOfSolutions++;
				//for (int y = 0; y < n; y++)
				//{
				//	for (int x = 0; x < n; x++)
				//	{
				//		if (queenPositions[y] == x)
				//		{
				//			cout << 'Q' << ' ';
				//		}
				//		else
				//		{
				//			cout << '*' << ' ';
				//		}
				//	}
				//	cout << endl;
				//}
				//cout << endl;
			}

			if (hasSpot)
			{
				row++;
			}else
			{
				//Basically when it backtracks it gets rid of all memory of pieces from the last attempt
				int rowThatNeedsToBeErased = row;
				while (rowThatNeedsToBeErased < n){
					for (int collumnToBeErased = 0; collumnToBeErased < n; collumnToBeErased++){
						previouslyTried[n*rowThatNeedsToBeErased + collumnToBeErased ] = false;
					}
					rowThatNeedsToBeErased++;
				}
				row--;
			}
		}
	}

	delete [] queenPositions;
	delete [] previouslyTried;
	return numOfSolutions;
}

int main()
{
	int n;
	cout << "What size board would you like to solve for ";
	cin >> n;
	int solutions = nQueens(n);
	cout << endl << "There are " << solutions << " solutions";

	cin.get();
	cin.ignore();
	return 0;
}
