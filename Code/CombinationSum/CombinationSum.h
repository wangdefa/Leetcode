#include<vector>
#include<stack>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include "assert.h"
#include "stdint.h"
using namespace std;

void display(const vector<vector<int>>& res)
{
	cout << "res: " << endl;
	for (auto single_res : res){
		for (auto ele : single_res){
			cout << ele << "\t";
		}
		cout << endl;
	}
}

class Solution {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end(), [](int x, int y){return x > y; });
		return combinationSum(candidates, target, 0);
	}

	vector<vector<int>> combinationSum(const vector<int>& nums, int tar, int beg){
		// the special case
		vector<vector<int>> res;
		if (tar == 0){
			res.resize(1); // there is only one solution here( no ele)
			return res;
		}
		if (nums.size() == beg || tar < 0){
			res.resize(0); // there is no solution here( no ele)
			return res;
		}

		// recursive
		// recursive
		int max_index = beg;
		while (max_index < nums.size() && nums[max_index] == nums[beg]) max_index++;
		for (int i = 0; i <= max_index - beg; i++){
			int new_tar = tar - nums[beg] * i;
			vector<vector<int>> tmp;
			tmp = combinationSum(nums, new_tar, max_index); // find the new target from the next ele

			// we find some result
			if (!tmp.empty()){
				vector<int> suffix;
				for (int j = 0; j < i; j++) suffix.push_back(nums[beg]);
				for (vector<int> & vec : tmp) vec.insert(vec.end(), suffix.begin(), suffix.end());
				for (vector<int> & vec : tmp) res.push_back(vec);
			}
		}
		
		//display(res);
		return res;
	}
};

