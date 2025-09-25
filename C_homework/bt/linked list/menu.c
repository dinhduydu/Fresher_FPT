#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "Linked_List.h"
#include "menu.h"
/*********************************************************************************************************
 * Variable
*********************************************************************************************************/

/* Create ArrayNode array to store address of struct Student element and store next node */
static Node_t ArrayNode[MAX_NODE];
/**********************************************************************************************************
 * Function 
**********************************************************************************************************/

/* Create a static linked list */
void Menu_InitialStaticLinkedList(LinkedList_t *list)
{   
    /***
     * index  0    1    2    3    4    5    6    7    8    9  
     * data  -1   -1   -1   -1   -1   -1   -1   -1   -1   -1
     * pNext  1    2    3    4    5    6    7    8    9   -1        -1 is end of list
     */
    uint8_t index = 0;
    list->head = 0xFF;
    list->tail = 0xFF;
    list->freelist = 0; 
    /* Create a newly linked list with all node 'll be blank */
    for(index = 0; index < MAX_NODE; index++)
    {
        strcpy(ArrayNode[index].data.Account_Name, "0xFF" );
        strcpy(ArrayNode[index].data.Name,"0xFF");
        ArrayNode[index].data.Average_Score = 0xFF;
        strcpy(ArrayNode[index].data.Student_Code, "0xFF");
        ArrayNode[index].pNext = index + 1;
    }
    ArrayNode[MAX_NODE - 1].pNext = 0xFF; /* End of List */
    printf("\n\tInitial linked list successful\n");
    printf("\n\tInit head, freelist and tail:\n");
    printf("\n\thead = %u", list->head);
    printf("\tfreelist = %u", list->freelist);
    printf("\ttail = %u\n", list->tail);
    printf("\n\tIt mean this static linked list has not any element yet.\n");
    for(index = 0; index < MAX_NODE; index++)
    {
        printf("\n\tElement %u with index %u is:\n", index+1, index);
        printf("\tArrayNode[%u].data.Name = %s\n", index, ArrayNode[index].data.Name );
        printf("\tArrayNode[%u].data.Account_Name = %s\n", index, ArrayNode[index].data.Account_Name );
        printf("\tArrayNode[%u].data.Average_Score = %f\n", index, ArrayNode[index].data.Average_Score );
        printf("\tArrayNode[%u].data.Student_Code = %s\n", index, ArrayNode[index].data.Student_Code );
        printf("\tArrayNode[%u].pNext = %u\n", index, ArrayNode[index].pNext);
    }
    printf("\n\tThe form of static linked list you see is: \n");
    printf("\t+----+----+----+----+----+----+----+----+----+----+\n");
    printf("  index |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |\n");
    printf("\t+----+----+----+----+----+----+----+----+----+----+\n");
    printf("  data  |0xFF|0xFF|0xFF|0xFF|0xFF|0xFF|0xFF|0xFF|0xFF|0xFF|\n");
    printf("\t+----+----+----+----+----+----+----+----+----+----+\n");
    printf("  pNext |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |0xFF|\n");
    printf("\t+----+----+----+----+----+----+----+----+----+----+\n");
    printf("\n\t\tPress any key to go Menu page!\n");
    getch();
}

/* Pick a node from the backup list to allocate space */
uint8_t Menu_MallocNode (void)
{
    uint8_t index = 0; /* Declare variable to search node has empty data */
    /* Find the blank node */
    for (index = 0; index < MAX_NODE; index ++)
    {
        if (ArrayNode[index].data.Average_Score == 0xFF)
        {
            break;
        }
    }
    return index; /* Return index of node has empty data */
}

void Menu_FindTail(LinkedList_t *list)
{
    uint8_t index;  /* Declare a variable to find tail */
    while ((ArrayNode[index].data.Average_Score != 0xFF) && (ArrayNode[index].pNext == 0xFF))
    {
        index ++;
    }
    list->tail = index;
}

/* Create a node of static linked list */
uint8_t Menu_CreateNode(void) /* With param is address of Student Struct */
{   
    uint8_t index = Menu_MallocNode(); /* Allocate space by get index of empty node */
    Menu_Enter_Student_Data(index); /* Enter data of student */
    printf("\t\t<Done enter data student!>\n");
    return index;
}

void Menu_AssignTail(LinkedList_t *list, uint8_t index)
{
    uint8_t tempTail;
    tempTail = ArrayNode[index].pNext;
    uint8_t tempPrevTail = index; 
    while (tempTail != 0xFF)
    {
        tempPrevTail = tempTail;
        tempTail = ArrayNode[tempTail].pNext;
    }
    list->tail = tempPrevTail;
}

void Menu_Enter_Student_Data (uint8_t index)
{
    uint32_t enterdata = 0;
    printf("\t<Press any key to clear input buffer on keyboard.>\n"); /* Should clear input buffer after use scanf, 
                                                                    and if not when use gets, we "ll force problem  */
    while (getchar() != '\n'); /* take one bye one character from buffer until get the'\n' character */
    /* Enter data into student struct */
    printf("\n\tEnter Student Code: ");
    gets(ArrayNode[index].data.Student_Code);
    printf("\n\tEnter Name: ");
    gets(ArrayNode[index].data.Name);  
    printf("\n\tEnter Account_Name: ");
    gets(ArrayNode[index].data.Account_Name);
    printf("\n\tEnter Average Score: ");
    do 
    {
        scanf("%u", &enterdata);
        if (enterdata > 10)
        {
            printf("\nInvalid: score exceed 10, Enter again: ");
        }
    }
    while(enterdata > 10);
    ArrayNode[index].data.Average_Score = (uint8_t)enterdata;
}

void Menu_AddAtBeginning (LinkedList_t *list)
{
    /***
     * Befor    E->C->A->B->D     Head = 4     FreeList = 5     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E   -1   -1   -1   -1   -1
     * pNext    1    3    0   -1    2    6    7    8    9   -1
     * After    F->E->C->A->B->D   Head = 5     FreeList = 6     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E    F   -1   -1   -1   -1
     * pNext    1    3    0   -1    2    4    7    8    9   -1
     */
    uint8_t tempHead = list->head; /* Now, head pointing the first elment of list, not new node*/
    uint8_t index = Menu_CreateNode(); /* Get index of new node */
    list->head = index; /* Now, head pointing the new node insteate of old first elment of list */
    list->freelist = ArrayNode[index].pNext; /* When add, freelist has pNext of new created node */
    ArrayNode[index].pNext = tempHead; /* New node points to that old first element of list  */
    Menu_AssignTail(list, index); /* Assert tail point true location */
    printf("\n\tUsers should check what they have entered and press any key to switch page.\n");
    getch(); /* Users double check what they have entered  */
}

uint8_t Menu_FindNearTail(uint8_t tempTail, uint8_t nearTail)
{
    printf("\n\ttempTail is %u", tempTail);
    while(ArrayNode[nearTail].pNext != tempTail)
    {
        printf("\n\tneartail = %u, ArrayNode[nearTail].pNext is %u", nearTail, ArrayNode[nearTail].pNext);
        nearTail ++;
    }
    return nearTail;
} 

void Menu_AddAtEnd (LinkedList_t *list)
{
    /***
     * Befor    E->C->A->B->D      Head = 4     FreeList = 5     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E   -1   -1   -1   -1   -1
     * pNext    1    3    0   -1    2    6    7    8    9   -1
     * After    E->C->A->B->D->F   Head = 4     FreeList = 6     Tail = 6
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E    F   -1   -1   -1   -1
     * pNext    1    3    0    5    2   -1    7    8    9   -1
     */
    uint8_t tempTail;
    uint8_t index;
    uint8_t nearTail;
    if (list->head == 0xFF)
    {
        Menu_AddAtBeginning(list);
    }
    else
    {
        tempTail = list->tail; /* Declare a temporary variable to be used for contain index of old last node of list */
        index = Menu_CreateNode(); /* Find a new space to contain new node*/
        list->freelist = ArrayNode[index].pNext;
        ArrayNode[tempTail].pNext = index;
        list->tail = index; /* Now, tail containing index of new last node of list */
        ArrayNode[index].pNext = 0xFF;
        getch();
    }
}
void Menu_AddAtIndex(LinkedList_t *list, uint8_t posInList)
{
    /***
     * Befor    E->C->A->B->D      Head = 4     FreeList = 5     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E   -1   -1   -1   -1   -1
     * pNext    1    3    0   -1    2    6    7    8    9   -1
     * After    E->C->F->A->B->D   Head = 4     FreeList = 6     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E    F   -1   -1   -1   -1
     * pNext    1    3    5   -1    2    0    7    8    9   -1
     */
    uint8_t index;
    /* Sequential search */
    uint8_t ptr = list->head; /* use to search position in list */
    printf("\n\n\tlist head is %u\n", list->head);
    if (posInList = 0 || list->head == 0xFF)
    {
        Menu_AddAtBeginning(list);
    }
    else 
    {
        index = Menu_MallocNode();
        /* Find the position of the list need to be inserted  */
        printf("\n\tindex is %u\n", index);
        for (index = 1; index < posInList; index++)
        {
            printf("\n\tPOSITION is %u", posInList);
            ptr = ArrayNode[ptr].pNext; /* Head point to each element of list until find a node that need to find */
            printf("ArrayNode[%u].pNext is: %u", ptr, ArrayNode[ptr].pNext);
        }
        if (ptr == 0xFF)
        {
            printf("ArrayNode[%u].pNext is: %u", ptr, ArrayNode[ptr].pNext);
            /* It is mean that posInList is end of list */
            Menu_AddAtEnd(list);
        }
        else
        {
            ArrayNode[ptr].pNext = index; /* Node in posInList points to new node instead of old next node */
            list->freelist = index;
            ArrayNode[index].pNext = ptr; /* New node points to the old next node */
        }
    }
}

void Menu_DeleteFromBeginning (LinkedList_t *list)
{
    /***
     * Befor    E->C->A->B->D      Head = 4     FreeList = 5     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E   -1   -1   -1   -1   -1
     * pNext    1    3    0   -1    2    6    7    8    9   -1
     * After    C->A->B->D         Head = 2     FreeList = 4     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D   -1   -1   -1   -1   -1   -1
     * pNext    1    3    0   -1    5    6    7    8    9   -1
     */
    uint8_t tempHead; /* Save index of first node in list */
    uint8_t tempFreeList; /* Use to save freelist, prepare for assigning value in pNext of deleted node */
    tempHead = list->head; 
    tempFreeList = list->freelist;
    list->head = ArrayNode[tempHead].pNext; /* Head points to next node of deleted node */
    /* Clear data in deleted node */
    strcpy(ArrayNode[tempHead].data.Account_Name, "0xFF" );
    strcpy(ArrayNode[tempHead].data.Name,"0xFF");
    ArrayNode[tempHead].data.Average_Score = 0xFF;
    strcpy(ArrayNode[tempHead].data.Student_Code, "0xFF");
    ArrayNode[tempHead].pNext = tempFreeList; /* pNext of deleted node equals old freelist to certain that deleted node doesn't point 
                                                    any node of list */
    list->freelist = tempHead; /* Freelist equals index of deleted node */
    printf("\n\tDone deleleted! Please go back Menu page, if you continue deleted, this will be occured bug.");
    getch();
}

void Menu_DeleteFromEnd (LinkedList_t *list)
{
    /***
     * Befor    E->C->A->B->D      Head = 4     FreeList = 5     Tail = 3
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C    D    E   -1   -1   -1   -1   -1
     * pNext    1    3    0   -1    2    6    7    8    9   -1
     * After    E->C->A->B         Head = 4     FreeList = 3     Tail = 1
     * index    0    1    2    3    4    5    6    7    8    9 
     * Name     A    B    C   -1    E   -1   -1   -1   -1   -1
     * pNext    1   -1    0    5    2    6    7    8    9   -1
     */
    uint8_t nearTail; /* Declare a variable to search element near tail */
    uint8_t tempTail = list->tail; /* Declare a variable to save old tail, prepare for assigning value in near Tail element */
    uint8_t tempFreeList = list->freelist; /* Declare a variable to save old freelist */
    nearTail = Menu_FindNearTail(tempTail, nearTail);
    /* Find near tail */
    /* Clear data in deleted node */
    strcpy(ArrayNode[tempTail].data.Account_Name, "0xFF" );
    strcpy(ArrayNode[tempTail].data.Name,"0xFF");
    ArrayNode[tempTail].data.Average_Score = 0xFF;
    strcpy(ArrayNode[tempTail].data.Student_Code, "0xFF");
    ArrayNode[nearTail].pNext = 0xFF; /* Near tail element points to end of list */
    list->freelist = tempTail; /* Freelist has index of deleted node */
    getch();
}

void Menu_DeleteFromIndex (uint8_t pos)
{
    uint8_t indexPrev; /* Declare a variable to search previous element */
    uint8_t tempPrev; /* Declare a variable to save index of deleted node */
    uint8_t tempAfter; /* Save index of next node which deleted node had pointed to  */
    LinkedList_t list;
    /* Clear data in this position */
    strcpy(ArrayNode[pos].data.Account_Name, "0xFF" );
    strcpy(ArrayNode[pos].data.Name,"0xFF");
    ArrayNode[pos].data.Average_Score = 0xFF;
    strcpy(ArrayNode[pos].data.Student_Code, "0xFF");
    tempAfter = ArrayNode[pos].pNext; /* Save index of node which ArrayNode[pos] had pointed to */
    ArrayNode[pos].pNext = list.freelist; /* take index of node was lastly added and certain that this deleted node point doesn't point 
                                            to any element of list */
    /* Find the previous node */
    while(ArrayNode[indexPrev].pNext != pos)
    {
        indexPrev ++;
    }
    tempPrev = ArrayNode[indexPrev].pNext; /* Save index of deleted node which previous node point to (this deleted node) */
    ArrayNode[indexPrev].pNext = tempAfter; /* Previous node point to the next node instead of this deleted node */
}

void Menu_PrintList (LinkedList_t *list)
{
    uint8_t index;
    for(index = 0; index < MAX_NODE; index++)
    {
        printf("\n\n\tElement %u with index %u:\n", index+1, index);
        printf("\tArrayNode[%u].data.Name = %s\n", index, ArrayNode[index].data.Name );
        printf("\tArrayNode[%u].data.Account_Name = %s\n", index, ArrayNode[index].data.Account_Name );
        printf("\tArrayNode[%u].data.Average_Score = %f\n", index, ArrayNode[index].data.Average_Score );
        printf("\tArrayNode[%u].data.Student_Code = %s\n", index, ArrayNode[index].data.Student_Code );
        printf("\tArrayNode[%u].pNext = %u\n", index, ArrayNode[index].pNext);
    }
    printf("\n\t====================================================\n");
    printf("\n\thead = %u", list->head);
    printf("\tfreelist = %u", list->freelist);
    printf("\ttail = %u\n", list->tail);
    printf("\n\t\t<Press any key to go back Menu.>");
    getch();
}

void Menu_SearchByName (LinkedList_t *list)
{
    char str[30];
    uint8_t ptr = list->head;
    Student_t returnValue;
    Student_t enterValue;
    printf("\n\tEnter the name you want to search for: ");
    gets(str);
    printf("\n\tSearching.....\n");
    while ((strcmp(ArrayNode[ptr].data.Name,str) !=0)||(ptr = 0xFF))
    {
        printf("strcmp(ArrayNode[ptr].data.Name,str) is: %u",strcmp(str,ArrayNode[ptr].data.Name));
        printf ("\n");
        ptr = ArrayNode[ptr].pNext;
    }
    if (ptr = 0xFF)
    {
        printf("\n\tData not found\n");
        getch();
    }
    else
    {
        printf("\n\tArrayNode[%u].data.Name is %u", ptr, ArrayNode[ptr].data.Name);
        printf("\n\tArrayNode[%u].data.AccountName is %u", ptr, ArrayNode[ptr].data.Account_Name);
        printf("\n\tArrayNode[%u].data.StudentCode is %u", ptr, ArrayNode[ptr].data.Student_Code);
        printf("\n\tArrayNode[%u].data.AverageScore is %u", ptr, ArrayNode[ptr].data.Average_Score);
        printf("\n\tArrayNode[%u].pNext is %u\n", ptr, ArrayNode[ptr].pNext);
    }
}

void Menu_SearchByAccount (LinkedList_t *list)
{
    char str[6];
    uint8_t ptr = list->head;
    printf("\n\tEnter the Account name you want to search for: ");
    gets(str);
    printf("\n\tSearching.....\n");
    while ((strcmp(ArrayNode[ptr].data.Account_Name,str) !=0)&&(ptr = 0xFF))
    {
         ptr = ArrayNode[ptr].pNext;
    }
    if (ptr = 0xFF)
    {
        printf("\n\tData not found\n");
        getch();
    }
    else
    {
        printf("\n\tArrayNode[%u].data.Name is %u", ptr, ArrayNode[ptr].data.Name);
        printf("\n\tArrayNode[%u].data.AccountName is %u", ptr, ArrayNode[ptr].data.Account_Name);
        printf("\n\tArrayNode[%u].data.StudentCode is %u", ptr, ArrayNode[ptr].data.Student_Code);
        printf("\n\tArrayNode[%u].data.AverageScore is %u", ptr, ArrayNode[ptr].data.Average_Score);
        printf("\n\tArrayNode[%u].pNext is %u\n", ptr, ArrayNode[ptr].pNext);
    }
}

void Menu_SearchByCode (LinkedList_t *list)
{
    char str[12];
    uint8_t ptr = list->head;
    printf("\n\tEnter student code you want to search for: ");
    gets(str);
    printf("\n\tSearching.....\n");
    while ((strcmp(ArrayNode[ptr].data.Student_Code,str) !=0)&&(ptr = 0xFF))
    {
         ptr = ArrayNode[ptr].pNext;
    }
    if (ptr = 0xFF)
    {
        printf("\n\tData not found\n");
        getch();
    }
    else
    {
        printf("\n\tArrayNode[%u].data.Name is %u", ptr, ArrayNode[ptr].data.Name);
        printf("\n\tArrayNode[%u].data.AccountName is %u", ptr, ArrayNode[ptr].data.Account_Name);
        printf("\n\tArrayNode[%u].data.StudentCode is %u", ptr, ArrayNode[ptr].data.Student_Code);
        printf("\n\tArrayNode[%u].data.AverageScore is %u", ptr, ArrayNode[ptr].data.Average_Score);
        printf("\n\tArrayNode[%u].pNext is %u\n", ptr, ArrayNode[ptr].pNext);
    }
}

void Menu_SearchByScore (LinkedList_t *list)
{
    uint32_t score;
    uint8_t count;
    uint8_t checkScore;
    uint8_t ptr = list->head;
    printf("\n\tlist.head is %u\n", list->head);
    printf("\nptr is: %u\n",ptr);
    printf("\n\tEnter score which you want to search for: ");
    scanf("%u",&score);
    checkScore = (uint8_t)score;
    printf("score is %u\n", checkScore);
    printf("\n\tSearching.....\n");
    while (ptr != 0xFF)
    {
        if (ArrayNode[ptr].data.Average_Score == checkScore)
        {
            count++;
            printf("\n\tArrayNode[%u].data.Name is %s", ptr, ArrayNode[ptr].data.Name);
            printf("\n\tArrayNode[%u].data.AccountName is %s", ptr, ArrayNode[ptr].data.Account_Name);
            printf("\n\tArrayNode[%u].data.StudentCode is %s", ptr, ArrayNode[ptr].data.Student_Code);
            printf("\n\tArrayNode[%u].data.AverageScore is %u", ptr, ArrayNode[ptr].data.Average_Score);
            printf("\n\tArrayNode[%u].pNext is %u\n", ptr, ArrayNode[ptr].pNext);
        }
        ptr = ArrayNode[ptr].pNext;
    }
    if(count == 0)
    {
        printf("\n\tData not found\n");
    }
    getch();
}

uint8_t Menu_LengthList(LinkedList_t *list)
{
    uint8_t count;
    uint8_t ptr = list->head;
    while (ArrayNode[ptr].pNext != 0xFF)
    {
        ptr = ArrayNode[ptr].pNext;
        count++;
    }
    return count;
}

void Menu_CopyScore (LinkedList_t *list, uint8_t *CopyScore,uint8_t length)
{
    uint8_t index;
    uint8_t ptr = list->head;
    for (index = 0; index < length - 1; index++)
    {
        CopyScore[index] = ArrayNode[ptr].data.Average_Score;
        ptr = ArrayNode[ptr].pNext;
    }
}

void Menu_QuickSort(LinkedList_t *list, uint8_t *CopyScore, uint8_t left, uint8_t right)
{
    uint8_t pivot;
    uint8_t i;
    uint8_t j;
    uint8_t temp;
    if (list->head == list->tail)
    {
        return;
    }
    else
    {
        if (left < right)
        {
            pivot = left;
            i = left;
            j = right;
        }
        while (i < j) /* List with more than 0 elements */
        {
            while ((CopyScore[i] < CopyScore[pivot]) && (i < right))
            {
                i++;
            }
            while (CopyScore[j] > CopyScore[pivot])
            {
                j--;
            }
            if( i <= j)
            {
                /* Swap */
                temp = CopyScore[i];
                CopyScore[i] = CopyScore[j];
                CopyScore[j] = temp;
            }
        }
        temp = CopyScore[pivot];
        CopyScore[pivot] = CopyScore[j];
        CopyScore[j] = temp;
        Menu_QuickSort(list, CopyScore, left, j-1);
         Menu_QuickSort(list, CopyScore, j+1, left);
    }
}

char Menu_SearchDisplay(void)
{
    char type;
    char c;
    /* Shows all options search for user and helps user choose option what they want. */
    printf("\n\t                              SEARCH\n");
    printf("\n\t +-------------------------------------------------------------------+");
    printf("\n\t |        1. Press '1' to search by Student code.                    |");
    printf("\n\t |        2. Press '2' to search by Student name.                    |");
    printf("\n\t |        3. Press '3' to search by Student account.                 |");
    printf("\n\t |        4. Press '4' to search by Student score.                   |");
    printf("\n\t |        5. Press '5' to print list.                                |");
    printf("\n\t |        6. Press '6' to go back Menu.                              |");
    printf("\n\t |        7. Enter '0' to Exit.                                      |");
    printf("\n\t +-------------------------------------------------------------------+\n");
    do 
    {
        printf("\n\tEnter your choice = ");
    }
    while ((scanf("%c%c", &type, &c)!=2||c!='\n')&&clean_stdin());
    return type;
}

char Menu_Display(void)
{
    char type;
    char c;
    printf("\n\t                                MENU\n" );
    printf("\n\t +------------------------------------------------------------------+");
    printf("\n\t |        1. Press '1' to add data student.                         |");
    printf("\n\t |        2. Press '2' to delete data student.                      |");
    printf("\n\t |        3. Press '3' to search data student.                      |");
    printf("\n\t |        4. Press '4' to sort list.                                |");
    printf("\n\t |        5. Press '5' to print list.                               |");
    printf("\n\t |        6. Press '0' to exit.                                     |");
    printf("\n\t +------------------------------------------------------------------+\n");
    do 
    {
        printf("\n\tEnter your choice = ");
    }
    while ((scanf("%c%c", &type, &c)!=2||c!='\n')&&clean_stdin());
    return type;
}

void Menu(LinkedList_t *list)
{
    char choose;/* Declare a variable to choose options. */
    do
    {
    /**
     * @Show Menu which shows all options for user and helps user choose option what they want
    */
        system("cls");
        choose = Menu_Display();
        switch(choose)
        {
            case '1': 
            {   
                LinkedList_AddElement(list); 
                break;
            }
            case '2': 
            { 
                LinkedList_DelElement(list);
                break;
            }
            case '3': 
            { 
                LinkedList_Search(list) ;
                break;
            }
            case '4': 
            { 
                LinkedList_Sort(list);
                break;
            }
            case '5':
            {
                Menu_PrintList (list);
                break;
            }
            case '0': 
            {
                exit(0);
            }
            default: 
            {
                printf("\nEnter Again!");
            }
        }
    } 
    while (choose!='0');
}
