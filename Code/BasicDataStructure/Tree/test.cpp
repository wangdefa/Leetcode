#include "tree.h"

int main(){
	// input 
	Tree tree(10);
	tree.Traverse(Tree::FIRST);
	std::cout << std::endl;
	tree.Traverse(Tree::MIDDLE);
	std::cout << std::endl;
	tree.Traverse(Tree::LAST);
	std::cout << std::endl;

	tree.Serilize(tree.head, "binary_tree");
	return 0;
}
