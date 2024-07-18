#include "linked_list.h"

int main(void)
{
	Node *list = InitList();
	AddNode(list, "Hello");
	AddNode(list, "World");
	DeleteList(list);
	for (;;)
		;
}