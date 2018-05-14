#include<queue>
#include <iostream>
#include <iomanip>  
#include "assert.h"
#include "stdint.h"

int main(){
	// input 
	std::queue<uint32_t> q;
	for (uint32_t i =0; i < 10; i++)
	{
		q.push(i); // insert element in the end of the queue
	}

	std::cout << q.front() << std::endl; // get the element in the front of the queue
	q.pop(); // pop out the element in the front of the queue
	std::cout << q.front() << std::endl;
	q.pop();
	std::cout << q.size() << std::endl;
	return 0;
}
