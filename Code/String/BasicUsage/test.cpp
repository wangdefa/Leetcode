#include <string>
#include <iostream>

int main(){
	std::string src = "Hello";
	std::cout << "The input string is: " << src << std::endl;

	// 1. Get the size of the str
	std::cout << "The length of the str: " << src.size() << std::endl;

	// 2. Get the sub_str of the str
	std::cout << "The sub_str(2,4) of the str: " << src.substr(2, 4) << std::endl;

	// 3. Call by index
	std::cout << "The src[4] of the str: " << src[4] << std::endl;

	// 4. Find the start index of a special character
	std::cout << "The first index of l the str: " << src.find('l') << std::endl;
	std::cout << "The first index of a the str: " << int(src.find('a')) << std::endl;
	return 0;
}
