/**
 * @file menu.h
 * @author Dinh Duy Du (DuDDu@fsoft.com)
 * @brief Provide static functions
 * @version 0.1
 * @date 2022-07-17
 * 
 * @copyright No Copyright (c) 2022
 * 
 */
/**********************************************************************************************************************
 * Include
 **********************************************************************************************************************/
#ifndef _MENU_H_
#define _MENU_H_

/**********************************************************************************************************************
 * Define Macro
 **********************************************************************************************************************/
#define MAX_NODE     10 /* The maximum length of the Static linked list  */

#include "Linked_List.h"


/****************************************************************************************************************************
 * Function prototype
****************************************************************************************************************************/






/**
 * @brief Init signly linked list
 * 
 */
void Menu_InitialStaticLinkedList (LinkedList_t *list);

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t Menu_MallocNode (void);

/**
 * @brief 
 * 
 */
void Menu_FindTail(LinkedList_t *list);

/**
 * @brief Create node
 * 
 * @param student 
 * @return Node* 
 */
uint8_t Menu_CreateNode(void);

/**
 * @brief 
 * 
 * @return Student_t* 
 */
void Menu_Enter_Student_Data (uint8_t index);

/**
 * @brief Insert a new node at begining of linked list
 * 
 */
void Menu_AddAtBeginning (LinkedList_t *list);

/**
 * @brief Insert a new node at the end of Linked List.
 * 
 */
void Menu_AddAtEnd (LinkedList_t *list);

// /**
//  * @brief Insert a new node at index.
//  * @param a: Address of the pointer that is the head pointer of the list.
//  * @return true if insert SUCCESSED, false if insert FAILED
// */
// LinkedList_t* Menu_AddAtIndex(LinkedList_t a, uint8_t index, uint8_t data);

/**
 * @brief 
 * 
 * @param posInList 
 */
void Menu_AddAtIndex(LinkedList_t *list, uint8_t posInList);

// /**
//  * @brief 
//  * 
//  * @param head 
//  */
// void Menu_FreeMemory(Node* head);


/**
 * @brief 
 * 
 */
void Menu_DeleteFromBeginning (LinkedList_t *list);

// /**
//  * @brief 
//  * 
//  * @param head 
//  * @return LinkedList* 
//  */
// LinkedList_t* Menu_DeleteFromBeginning(Node_t* head);

/**
 * @brief 
 * 
 */
void Menu_DeleteFromEnd (LinkedList_t *list);
// /**
//  * @brief 
//  * 
//  * @param head 
//  * @return LinkedList* 
//  */
// LinkedLis_t* Menu_DeleteFromEnd(Node_t* head);

// /**
//  * @brief Delete a new node at index.
//  * @param a: Address of the pointer that is the head pointer of the list.
//  * @return true if insert SUCCESSED, false if insert FAILED
// */
// LinkedList_t* Menu_DeleteFromIndex(Node_t* head, int index);

/**
 * @brief 
 * 
 * @param tempTail 
 * @param nearTail 
 * @return uint8_t 
 */
uint8_t Menu_FindNearTail(uint8_t tempTail, uint8_t nearTail);

/**
 * @brief 
 * 
 * @param pos 
 */
void Menu_DeleteFromIndex (uint8_t pos);

/**
 * @brief 
 * 
 */
void Menu_PrintList (LinkedList_t *list);

char Menu_SearchDisplay(void);
/**
 * @brief 
 * 
 */
void Menu_Search (LinkedList_t *list);



/**
 * @brief 
 * 
 * @param low 
 * @param high 
 */
void Menu_QuickSort(LinkedList_t *list, uint8_t *CopyScore, uint8_t left, uint8_t right);

/**
 * @brief Show program Menu
 */
void Menu (LinkedList_t *list);

uint8_t Menu_LengthList(LinkedList_t *list);

#endif/*_MENU_H_*/

