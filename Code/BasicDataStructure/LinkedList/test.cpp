#include "linkedList.h"

int main(){
	// input 
	LinkedList list;
	for (int32_t i = 0; i < 10; i++)
	{
		list.PushBack(i);
	}
	list.Serilize("The initial list");

	list.Reverse();
	list.Serilize("The list after reverse");

	list.PopBack();
	list.Serilize("The list after pop back");

	std::cout << "Cycle detection: " << list.HasCycle() << std::endl;
	list.tail->next = list.head->next; // head is a dummy Node
	std::cout << "Cycle detection after insert a cycle: " << list.HasCycle() << std::endl;
	return 0;
}
