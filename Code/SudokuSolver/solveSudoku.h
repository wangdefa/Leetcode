#include<vector>
#include<stack>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"
#include "stdint.h"
#define SIZE 9
using namespace std;

struct Node{
    int row;
    int col;
    char val;
    Node(int x, int y, char z) : row(x), col(y), val(z){}
    Node(){}
};

class Solution {
private:
	bool filled[SIZE * 3][SIZE];
	Node node_now;
	stack<Node> s_node;

public:
	vector<vector<char> > board;

public:
    Solution(){
        node_now = Node(-1, -1, 'a');
    }

public:
    void solveSudoku() {
        if (!initTable()) return; // the init problem is not solvable
        
        // begin to search
        Node node = Node(-1, -1, ' ');
        while(true){
            // Go ahead until we can't
            while (true){
                node = getNextNode();
				if (node.row == -1){
					fillBoard();
					return; // we can't get a empty position
				}
				if (!pushValAt(node.row, node.col, '1')) break;
				// fillDisplay(board, s_node);
            }
                                
            // we didn't find any valid next node
            while(true){
                if (s_node.empty()) return;
                node = s_node.top();
                s_node.pop();
				releaseTable(node.row, node.col, node.val);// Release this node
				if (pushValAt(node.row, node.col, node.val + 1)) break;
				// fillDisplay(board, s_node);
            }
        }  
        return; // we can't find the result
    }
    
	// before we exit, we should fill the board
	void fillBoard(){
        while (!s_node.empty()){
            Node node = s_node.top();
            board[node.row][node.col] = node.val;
            s_node.pop();
        }
    }
    
	// try to push in beg in the position (row, col) 
    bool pushValAt(int row, int col, char beg){
        for (int i = beg - '1'; i < 9; i++){
            // find a valid element to push in
            if(updateTable(row, col, '1' + i)){
                Node node(row, col, '1' + i);
                s_node.push(node); // add this node into stack
                node_now = node; 
                return true;
            }
        }
        return false;
    }
    
    // Init the table, if have been conflict, return false
    bool initTable()
    {
        node_now = Node(0, -1, ' '); // used as a guard

		for (int i = 0; i < 27; i++){
			for (int j = 0; j < 9; j++){
				filled[i][j] = false;
			}
		}

        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (board[i][j] != '.'){
                    if(!updateTable(i, j, board[i][j])) return false;
                }
            }
        }
        return true;
    }
   
	// when we do backtrace, we should release the table which have been occupied
	bool releaseTable(int row, int col, char val){
		assert(val != '.');
		int index = val - '1';
		int index_3_3 = (row / 3) * 3 + col / 3;
		if (filled[index_3_3][index] && filled[9 + row][index] && filled[18 + col][index]){
			filled[index_3_3][index] = false; // This means the index_3_3th square have element index
			filled[9 + row][index] = false; // the row th row contains the element index
			filled[18 + col][index] = false; // the col th col contains the element index
			return true;
		}

		return false;
	}

    // if this is not included, we will return true and update table, or we will return false.
    bool updateTable(int row, int col, char val){
        assert(val != '.');
        int index = val - '1';
        int index_3_3 = (row / 3) * 3 + col / 3;
        if (filled[index_3_3][index] || filled[9 + row][index] || filled[18 + col][index]) return false;
        else{
            filled[index_3_3][index] = true; // This means the index_3_3th square have element index
            filled[9 + row][index] = true; // the row th row contains the element index
            filled[18 + col][index] = true; // the col th col contains the element index
        }
        
        return true;
    }
    
    // if we get the next node, return the coordinate, or return Node(-1, -1, ' ')
    Node getNextNode(){
        for (int i = node_now.row * 9 + node_now.col + 1; i < 81; i++){
            if (board[i / 9][i % 9] == '.') return Node(i / 9, i % 9, ' ');
        }
        return Node(-1, -1, ' ');
    }

	// display situation of the board
	void display(bool flag){
		fillBoard();

		if (flag) cout << "The input is: " << endl;
		else cout << endl << "The solution is: " << endl;
		string col_spe = "*";
		string row_spe = "* *";
		for (uint8_t i = 0; i < SIZE; i++){
			if (i % 3 == 0){
				for (uint8_t j = 0; j < SIZE + 3; j++){
					cout << setw(5) << row_spe;
				}
				cout << endl;

				for (uint8_t j = 0; j < SIZE; j++){
					if (j % 3 == 0) cout << setw(5) << col_spe;
					cout << setw(5) << "";
				}
				cout << endl;
			}
			for (uint8_t j = 0; j < SIZE; j++){
				if (j % 3 == 0) cout << setw(5) << col_spe;
				cout << setw(5) << board[i][j];
			}
			cout << endl;

			for (uint8_t j = 0; j < SIZE; j++){
				if (j % 3 == 0) cout << setw(5) << col_spe;
				cout << setw(5) << "";
			}
			cout << endl;
		}
	}
};

