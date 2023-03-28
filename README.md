# data-structure-project-1
A data structure project that required knowledge about linked list, double pointers, dynamic memory allocation.

The program performs various operations on a linked list of student data. Here are the functions in the program and what they do:

- check(char *name): This function checks the class of the student and returns an integer value (0,1,2,3) depending on whether the class is Freshman, Sophomore, Junior, or Senior. If the class is not recognized, it returns 4.

- create_fill_node(FILE *infp): This function creates a new node for the linked list and fills it with data from a file.

- add_node_LL(student_node **p_head, student_node *ToAdd): This function adds a new node to the linked list. If the list is empty, the new node becomes the head of the list.

- traverse(student_node *head): This function traverses the linked list and prints the data of each node.

- Load_File_content_to_the_array(FILE *infp, student_node **arr): This function is used as the main function for creating a linked list by grouping the add_node_LL and check functions.

- fill_new_student(): This function is used to fill the node of a new student that needs to be added to the linked list.

- add_new_node_LL(student_node **p_head, student_node *ToAdd): This function adds a new student to the linked list.

- search_Add_a_new_student(student_node **arr, student_node *new_student): This function checks if the student's class is recognized and adds the new student to the appropriate linked list.

- delete(student_node *head, char *ID_delete): This function deletes the node with the specified ID from the linked list. If the node is the head of the list, the head pointer is updated to point to the next node in the list.
