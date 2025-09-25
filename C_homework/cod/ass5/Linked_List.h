/*Provide public functions*/
#ifndef LINKER_LIST_H_
#define LINKER_LIST_H_

/***************************************************************
*Definations
***************************************************************/


/***************************************************************
*Linked List Node
***************************************************************/
typedef struct Linkedlist_node_struct_t
{
    uint8_t* address_of_data;
    struct Linkedlist_node_struct_t* next;
} Node,*NodePtr;

/***************************************************************
*API
***************************************************************/
/**
 * @brief: Insert a new node to the list in ascending order of value
 * @param head: Address of the pointer that is the head pointer of the list
 *        new_node: Pointer to the new node which we want to insert
 * @return true if insert SUCCESSED, false if insert FAILED
*/
bool API_Insert (NodePtr* head,NodePtr new_mode);
bool API_Delete (NodePtr* list, uint8_t data);
void API_Menu (void);

#endif/*LINKERLIST_H_*/
