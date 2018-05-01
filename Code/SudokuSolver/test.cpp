#include "solveSudoku.h"

int main(){
	// input 
	char src[SIZE][SIZE] = {
	{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
	{ '6', '.', '.', '1', '9', '5', '.', '.', '.' },
	{ '.', '9', '8', '.', '.', '.', '.', '6', '.' },
	{ '8', '.', '.', '.', '6', '.', '.', '.', '3' },
	{ '4', '.', '.', '8', '.', '3', '.', '.', '1' },
	{ '7', '.', '.', '.', '2', '.', '.', '.', '6' },
	{ '.', '6', '.', '.', '.', '.', '2', '8', '.' },
	{ '.', '.', '.', '4', '1', '9', '.', '.', '5' },
	{ '.', '.', '.', '.', '8', '.', '.', '7', '9' }};
	Solution solution;
	for (uint8_t i = 0; i < SIZE; i++){
		solution.board.push_back(vector<char>(src[i], src[i] + SIZE));
	}

	// processing and display
	solution.display(true); // display the input
	solution.solveSudoku();
	solution.display(false); // display the input
	return 0;
}
