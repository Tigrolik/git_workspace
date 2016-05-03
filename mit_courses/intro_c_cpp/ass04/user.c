#include "bintree.h"

int main() {
	/*
	Insert your test code here. Try inserting nodes then searching for them.

	When we grade, we will overwrite your main function with our own sequence of
	insertions and deletions to test your implementation. If you change the
	argument or return types of the binary tree functions, our grading code
	won't work!
	*/

    insert_node(1, 2);
    insert_node(3, 4);
#if 0
    insert_node(3, 4);
    insert_node(3, 39);
    insert_node(8, 12);
    insert_node(5, 9);
#endif

    find_node_data(1);


	return 0;
}
