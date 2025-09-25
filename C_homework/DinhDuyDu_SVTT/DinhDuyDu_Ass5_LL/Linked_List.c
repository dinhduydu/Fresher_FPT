/*****************************************************************
* Include
****************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include "Linked_List.h"
#include "menu.h"
/***************************************************************
 * Code
 * Function
***************************************************************/

int clean_stdin()
{
    while(getchar()!='\n');
    return 1;
}

char Add_Display(void)
{
    char type;
    char c;
    system("cls");
    /* Show Menu which shows all delete element options for user */
    printf("\n\t                                ADD\n");
    printf("\n\t +------------------------------------------------------------------+");
    printf("\n\t |        1. Press '1' to add at begining of list.                  |");
    printf("\n\t |        2. Press '2' to add at end of list.                       |");
    printf("\n\t |        3. Press '3' to add at index.                             |");
    printf("\n\t |        4. Press '4' to go back Menu.                             |");
    printf("\n\t |        5. Press '0' to Exit.                                     |");
    printf("\n\t +------------------------------------------------------------------+\n");
    do 
    {
        printf("\n\tEnter your option = ");
    }
    while ((scanf("%c%c", &type, &c)!=2||c!='\n')&&clean_stdin());
    return type;
}

void LinkedList_AddElement(LinkedList_t *list)
{    
    uint32_t pos_check;
    uint8_t pos;
    char choose;
    do
    {
        choose=Add_Display();
        switch(choose)
        {
            case '1': 
                Menu_AddAtBeginning(list);
                break;
            case '2': 
                Menu_AddAtEnd(list);
                break;
            case '3': 
                printf("\tAdd element in position 0 -> 9: \t");
                do 
                {
                    scanf("%u", &pos_check);
                }
                while (pos_check > MAX_NODE);
                pos = (uint8_t)pos_check;
                printf("\n\t<pos la %u>\n", pos);
                Menu_AddAtIndex(list, pos);
                getch();
                break;
            case '4':
                Menu(list);
                break;
            case '0': 
                exit(1);
            default: 
                printf("\nEnter Again!");
                getch();
                break;
        }
    } 
    while (choose!='0');
}

char Del_Display(void)
{
    char type;
    char c;
    system("cls");
    /* Show Menu which shows all add element options for user */
    printf("\n\t                                DELETE\n");
    printf("\n\t +------------------------------------------------------------------+");
    printf("\n\t |        1. Delete at begining of list.                            |");
    printf("\n\t |        2. Delete at end of list.                                 |");
    printf("\n\t |        3. Delete at index.                                       |");
    printf("\n\t |        4. Press '4' to go back Menu.                             |");
    printf("\n\t |        5. Enter '0' to Exit.                                     |");
    printf("\n\t +------------------------------------------------------------------+");
    do 
    {
        printf("\n\tEnter  your option = ");
    }
    while ((scanf("%c%c", &type, &c)!=2||c!='\n')&&clean_stdin());
    return type;
}

void LinkedList_DelElement(LinkedList_t *list)
{
    uint32_t pos_check;
    uint32_t pos;
    char choose;
    system("cls");
    if (list->head == 0xFF)
    {
        printf("\n\tList is empty, cannot deleted any element in list.\n");
        printf("\n\t<Press any key to go back Menu page.>\n");
        getch();
    }
    else
    {
        do
        {
            choose = Del_Display();
            switch(choose)
            {
                case '1': 
                    Menu_DeleteFromBeginning(list); 
                    break;
                case '2': 
                    Menu_DeleteFromEnd(list); 
                    break;
                case '3': 
                    printf("Enter position to delete form index : \n");
                    scanf("%u", &pos_check);
                    if (pos_check > MAX_NODE - 1)
                    {
                        exit(1);
                    }
                    else
                    {
                        pos = (uint8_t)pos_check;
                    }                          
                    Menu_DeleteFromIndex(pos); 
                    break;
                case '4':
                    Menu(list);
                    break;
                case '0': 
                    exit(1);
                default: 
                    printf("\nEnter Again!");
                    getch();
                    break;
            }
        } 
        while (choose!='0');
    }
}

void LinkedList_Search(LinkedList_t *list)
{
    char choose;/* Declare a variable to choose options. */
    do
    {
    /* Show Menu which shows all options for user and helps user choose option what they want */
        system("cls");
        choose = Menu_SearchDisplay();
        switch(choose)
        {
            case '1':  
                Menu_SearchByCode (list);
                break;
            case '2': 
                Menu_SearchByName(list);
                break;
            case '3': 
                Menu_SearchByAccount(list);
                break;
            case '4': 
                Menu_SearchByScore(list);
                break;
            case '5':
                Menu_PrintList(list);
                break;
            case '6':   
                Menu(list);
                break;
            case '0': 
                exit(0);
            default: 
                printf("\n\t\t<Enter Again!>");
                getch();
                break;
        }
    } 
    while (choose!='0');
}

void LinkedList_Sort(LinkedList_t *list)
{
    printf("\n\tUse quick sort\n");
    uint8_t index;
    uint8_t length = Menu_LengthList(list);
    uint8_t CopyScore[length];
    Menu_CopyScore(list, CopyScore, length);
    Menu_QuickSort(list, CopyScore, 0, length -1);
    printf("\n\t\tAfter sort, list wil be:\n\n");
    for (index = 0; index < length; index++)
    {
        printf("\t\tElement %u is %u\n", index+1, CopyScore[index]);
    }
    getch();
}
