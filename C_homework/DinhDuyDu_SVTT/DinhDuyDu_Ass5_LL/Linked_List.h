/**
 * @file Linked_List.h
 * @author Dinh Duy Du (DuDDu@fsoft.com)
 * @brief Provide public library Static Linked list
 * @version 0.1
 * @date 2022-07-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/***************************************
 * Include
 **************************************/
#ifndef _LINKER_LIST_H_
#define _LINKER_LIST_H_
#include <stdint.h>



/***********************************************************************************************************************
 *  Define Struct type
 **********************************************************************************************************************/
/**
 * @brief Create student's attributes
 */
typedef struct Menu_Student
{
    char Student_Code[12];
    char Name[30];
    char Account_Name[6];
    uint8_t Average_Score;
}Student_t;

/**
 * @brief Define node: A Node has always a data item (contain data of struct) and a pNext pointer (point another node).
 */
typedef struct Node 
{
    /* A node has two components: data and a pointer to the next node*/
    Student_t data; /* data of Student */
    uint8_t pNext; /* cursor */
}Node_t;

/**
 * @brief Define Head used for sort, print
 */
typedef struct
{
    uint8_t head; /* When head has been created, it pointed nothing. It is mean that list is empty */
    uint8_t tail; /* Tail contain the index of last element of list */ 
    uint8_t freelist;
}LinkedList_t;



/*************************************************************************************************************************
 * Prototype
*************************************************************************************************************************/

/**
 * @brief Insert a new node to the list with 3 options:
 *         - Insert at begining of Linked List.
 *         - Insert at end of Linked List.
 *         - Insert at index.
 * @param a: Address of the pointer that is the head pointer of the list.
 *        index: Pointer to the new node which we want to insert
 *        data: Assign Data
 * @return true if insert SUCCESSED, false if insert FAILED
*/
void LinkedList_AddElement(LinkedList_t *list);

/**
 * @brief Delete a node in the list with 3 options:
 *        - Delete at begining of Linked List.
 *        - Delete at end of Linked List.
 *        - Delete at index.
 * @param a: Address of the pointer that is the head pointer of the lisut
 *        index: Pointer to the new node which we want to insert
 *        data: data we want to delete
 * @return true if delete SUCCESSED, false if delete FAILED
*/
void LinkedList_DelElement(LinkedList_t *list);

/**
 * @brief Insert a new node to the list in ascending order of value
 * @param a: Address of the pointer that is the head pointer of the list
 *        new_node: Pointer to the new node which we want to insert
 * @return true if add SUCCESSED, false if add FAILED
*/

void LinkedList_Search(LinkedList_t *list);

/**
 * @brief Sort the list in 2 mode:
 *        - Sort by point. (1)
 *        - Sort by name. (2)
 * @param a: Address of the pointer that is the head pointer of the list
 *        mode: User choose option 1 or 2
 * @return true if sort SUCCESSED, false if sort FAILED
*/
void LinkedList_Sort(LinkedList_t *list);

#endif/*_LINKERLIST_H_*/

