#include <stdlib.h>
#include "Linked_List.h"
#include "menu.h"


void main (void)
{
    LinkedList_t *list;                         /* Declare a pointer type LinkedList_t to access member of struct LinkedList: head, tail and freelist */
    LinkedList_t memory;                        /* Declare a variable to allocate memory for pointer type LinkedList_t */
    list = &memory;                             /* Before use pointer, must allocate memory location. */
    printf("\t\tSTATIC LINKED LIST\n");
    Menu_InitialStaticLinkedList(list);
    Menu(list);
}
