#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_NODE 	10 /* The maximum length of the Static linked list  */
typedef struct Menu_Student
{
    char Student_Code[12];
    char Name[30];
    char Account_Name[6];
    float Average_Score;
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

static Node_t ArrayNode[MAX_NODE];
/**
 * @brief Define Head used for sort, print
 */
typedef struct
{
    uint8_t head; /* When head has been created, it pointed nothing. It is mean that list is empty */
    uint8_t tail; /* Tail contain the index of last element of list */ 
    uint8_t freelist;
}LinkedList_t;


int clean_stdin()
{
    while(getchar()!='\n');
    return 1;
}





/* Create ArrayNode array to store address of struct Student element and store next node */

/**********************************************************************************************************
 * Function 
**********************************************************************************************************/

/* Create a backup linked list */
void Menu_InitialStaticLinkedList(LinkedList_t *list)
{   
    /***
     * index  0    1    2    3    4    5    6    7    8    9  
     * data  -1   -1   -1   -1   -1   -1   -1   -1   -1   -1
     * pNext  1    2    3    4    5    6    7    8    9   -1        -1 is end of list
     */
    uint8_t pos = 0;
    list->head = 0xFF;
    list->tail = 0xFF;
    list->freelist = 0; 
   
    /* Create a newly linked list with all node 'll be blank */
    for(pos = 0; pos < MAX_NODE; pos++)
    {
    	strcpy(ArrayNode[pos].data.Account_Name, "0xFF" );
        strcpy(ArrayNode[pos].data.Name,"0xFF");
        ArrayNode[pos].data.Average_Score = 0xFF;
        strcpy(ArrayNode[pos].data.Student_Code, "0xFF");
        ArrayNode[pos].pNext = pos + 1;
    }
    ArrayNode[MAX_NODE - 1].pNext = 0xFF; /* End of List */
    printf("\n\tInitial linked list successful\n");
    
    for(pos = 0; pos < MAX_NODE-1; pos++)
    {
    	printf("\n\tElement %u is:\n", pos+1);
        printf("\tArrayNode[%u].data.Name = %s\n", pos, ArrayNode[pos].data.Name );
        printf("\tArrayNode[%u].data.Account_Name = %s\n", pos, ArrayNode[pos].data.Account_Name );
        printf("\tArrayNode[%u].data.Average_Score = %f\n", pos, ArrayNode[pos].data.Average_Score );
        printf("\tArrayNode[%u].data.Student_Code = %s\n", pos, ArrayNode[pos].data.Student_Code );
        printf("\tArrayNode[%u].pNext = %u\n", pos, ArrayNode[pos].pNext);
        ArrayNode[pos].pNext = pos + 1;
    }
    printf("\n\tThe static linked list you see wil be formed: \n");
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

void Menu_Enter_Student_Data (uint8_t index)
{
    printf("\tIn function Menu_Enter_Student_Data(index), index is: %u\n", index);
    printf("\n\n\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
    printf("\tCalled Menu_Enter_Student_Data(index) and you will force this problem\n");
    uint32_t enterdata = 0;
    // uint8_t count = 0;
    char out = '\0';
    printf("\n\tEnter any key except 0 to continue entering student data.\n");
    printf("\n\tEnter '0' to stop entering student data.");
    // do
    // {
        // count++;
        // printf("count is %u", count);
    out=getch();
    if(out=='0')
    {
        exit(0);
    }
    printf("\tPress any key to clear buffer\n");
    while (getchar() != '\n'); /* take one bye one character from buffer until get the '\n' character */
        
    /* Enter data into Student struct */
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
        printf("Invalid: score exceed 10");
        }    
    }
    while(enterdata > 10);
    ArrayNode[index].data.Average_Score = (float)enterdata;
}

/* Pick a node from the backup list to allocate space */
uint8_t Menu_MallocNode (void)
{
	printf("\t-->Sau khi vao ham Menu_MallocNode\n");
	printf("\n\n\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
    uint8_t index = 0; /* Declare variable to search node has empty data */
    /* Find the blank node */
    for (index = 0; index < MAX_NODE; index ++)
    {
    	if (ArrayNode[index].data.Average_Score == 0xFF)
    	{
    		printf("\tArrayNode[%u].data.Average_Score = %f\n", index, ArrayNode[index].data.Average_Score );	
    		break;
    	}
    }
    printf("\tMalloc done and return index.\n");
    printf("\tindex is: %u\n", index);
    printf("\t-->Thoat ham malloc\n");
    return index; /* Return index of node has empty data */
}

void Menu_FindTail(LinkedList_t *list)
{
    uint8_t index;  /* Declare a variable to find tail */
    while ((ArrayNode[index].data.Name != "0xFF") && (ArrayNode[index].pNext == 0xFF))
    {
        index ++;
    }
    list->tail = index;
}

/* Create a node of static linked list */
uint8_t Menu_CreateNode(void) /* With param is address of Student Struct */
{   
    printf("\n\tSau khi vao ham create node\n");
    printf("\tArrayNode[0].pNext is: %u\n\n\n\n", ArrayNode[0].pNext);
    printf("\n\tCall Menu_MallocNode()\n");
    uint8_t index = Menu_MallocNode(); /* Allocate space*/
	printf("\n\tAfter call Menu_MallocNode()\n");    
	printf("\tIndex = malloc, so index is: %u\n", index);
    printf("\tCall Menu_Enter_Student_Data(index)\n");
    Menu_Enter_Student_Data(index); /* The data field is address of Student Struct - Student_1 */
    printf("\tDone enter!\n");

    
    printf("\n\n\n\tArrayNode[0].pNext is: %u\n", ArrayNode[0].pNext);
    printf("\tThoat ham Menu_CreateNode(void)\n");
    printf("\n\tVi la create node chu chua gan list.head, tail va freelist\n");
    return index;
}

void Menu_AssignTail(LinkedList_t *list, uint8_t index)
{
	uint8_t tempTail;
	tempTail = ArrayNode[index].pNext;
	printf("\n\n\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
	printf("\n\tSau khi vao ham Menu_AssignTail, ArrayNode[%u].pNext is: %u", index, ArrayNode[index].pNext);
	
	printf("\ttempTail is %u\n",tempTail);
	
	uint8_t tempPrevTail = index; 
	
	printf("\n\tBefore while (tempTail != 0xFF), list->tail is %u\n", list->tail);
	while (tempTail != 0xFF)
	{
		tempPrevTail = tempTail;
		printf("\ttempPrevTail is %u\n",tempPrevTail );
		tempTail = ArrayNode[tempTail].pNext;
		printf("\tArrayNode[%u].pNext is: %u", tempTail, ArrayNode[tempTail].pNext);
		printf("\ttempTail is %u\n",tempTail);
	}
	list->tail = tempPrevTail;
	printf("\tAfter while (tempTail != 0xFF),list->tail is: %u\n", list->tail);
}


/*-----------------------------------------Other operations of static linked list---------------------------------------------------*/
/***
 * Insert data into static linked list
 */
void Menu_AddAtBeginning (LinkedList_t *list)
{
	printf("\n\tHoi mat thoi gian 1 chut\n");
    printf("\tArrayNode[0].pNext is %u\n\n", ArrayNode[0].pNext);
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
    printf("\tAfter call Menu_AddAtBeginning (LinkedList_t *list)\n");
//    printf("\tlist head is: %u\n", list->head);
//    printf("\tlist.tail is: %u\n", list->tail);
//    printf("\tlist.freelist is: %u\n", list->freelist);
    uint8_t tempHead = list->head; /* Now, head pointing the first elment of list, not new node*/
    printf("\ttempHead is %u\n", tempHead);
    printf("\ttruoc khi create node, ArrayNode[0].pNext la:\n");
    printf("\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
    printf("\n\tSearching empty index by call Menu_CreateNode()\n");
    uint8_t index = Menu_CreateNode(); /* Get index of new node */


    printf("\n\n\tsau khi create node, ArrayNode[0].pNext la:\n");
    printf("\tArrayNode[0].pNext is %u\n", ArrayNode[0].pNext);

    printf("\n\tbat dau gan cac bien list.head, tail va freelist\n");
    printf("\tindex after create node is: %u\n", index);
    list->head = index; /* Now, head pointing the new node insteate of old first elment of list */
    printf("\tlist head is %u\n", list->head);
    list->freelist = ArrayNode[index].pNext; /* When add, freelist has pNext of new created node */
    printf("\tfreelist is %u\n", list->freelist);
    printf("\tlist.tail is %u\n", list->tail);
    ArrayNode[index].pNext = tempHead; /* New node points to that old first element of list  */
    printf("\tArrayNode[%u].pNext is %u\n", index, ArrayNode[index].pNext);
    printf("\tArrayNode[%u].pNext is %u\n", list->tail, ArrayNode[list->tail].pNext);
    printf("\tCall Menu_AssignTail(list, index = %u);\n", index);
    
    Menu_AssignTail(list, index);
    printf("\n\tSau khi call Menu_AssignTail\n");
    printf("\n\n\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
//    for(index = 0; index < MAX_NODE-1; index++)
//    {
//    	printf("\n\n\tElement %u is:\n", index+1);
//        printf("\tArrayNode[%u].data.Name = %s\n", index, ArrayNode[index].data.Name );
//        printf("\tArrayNode[%u].data.Account_Name = %s\n", index, ArrayNode[index].data.Account_Name );
//        printf("\tArrayNode[%u].data.Average_Score = %f\n", index, ArrayNode[index].data.Average_Score );
//        printf("\tArrayNode[%u].data.Student_Code = %s\n", index, ArrayNode[index].data.Student_Code );
//        printf("\tArrayNode[%u].pNext = %u\n", index, ArrayNode[index].pNext);
//        ArrayNode[index].pNext = index + 1;
//    }
//    printf ("\n\tElement %u is: \n", MAX_NODE),
//    printf("\tArrayNode[%u].data.Name = %s\n", index, ArrayNode[MAX_NODE-1].data.Name );
//    printf("\tArrayNode[%u].data.Account_Name = %s\n", index, ArrayNode[MAX_NODE-1].data.Account_Name );
//    printf("\tArrayNode[%u].data.Average_Score = %f\n", index, ArrayNode[MAX_NODE-1].data.Average_Score );
//    printf("\tArrayNode[%u].data.Student_Code = %s\n", index, ArrayNode[MAX_NODE-1].data.Student_Code );
//    printf("\tArrayNode[%u].pNext = %u\n", index, ArrayNode[MAX_NODE-1].pNext);
////    ArrayNode[MAX_NODE-1].pNext = 0xFF;
	printf("\n\n\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
}


char Add_Display(void)
{
    char type;
    char c;
//    system("cls");
    /* Show Menu which shows all add element options for user */
    printf("\n\t                                ADD\n");
    printf("\n\t +------------------------------------------------------------------+");
    printf("\n\t |        1. Add at begining of list.                               |");
    printf("\n\t |        2. Add at end of list.                                    |");
    printf("\n\t |        3. Add at index.                                          |");
    printf("\n\t |        4. Enter '0' to Exit.                                     |");
    printf("\n\t +------------------------------------------------------------------+\n");
    printf("\n\tEnter choice: ");
    do 
    {
        printf("\n\tEnter a character = ");
    }
    while ((scanf("%c%c", &type, &c)!=2||c!='\n')&&clean_stdin());
    return type;
}


void LinkedList_AddElement(LinkedList_t *list)
{
	printf("\n\tAfter call LinkedList_AddElement(LinkedList_t *list)\n");
    printf("\tlist.head is %u\n",list->head);
    printf("\tlist.tail is %u\n",list->tail);
    printf("\tlist.freelist is %u\n",list->freelist);
	printf("\n\n\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
    
    uint32_t pos_check;
    uint8_t pos;
    char choose;
    do
    {
        choose=Add_Display();
        switch(choose)
        {
            case '1': 
            { 
            	printf("\tBefor call Menu_AddAtBeginning (LinkedList_t *list)\n");

                Menu_AddAtBeginning(list);
                printf("\n\n\tAfter call Menu_AddAtBeginning(list)\n");
                	printf("\n\n\tArrayNode[0].pNext is %u", ArrayNode[0].pNext);
                break;
            }
            case '2': 
            { 
//                Menu_AddAtEnd(list);
                break;
            }
            case '3': 
            { 
                printf("pos: \n");
                scanf("%u", &pos_check);
                if (pos_check > MAX_NODE - 1)
                {
                    exit(1);
                }
                else
                {
                    pos = (uint8_t)pos_check;
                }
//                Menu_AddAtIndex(list, pos);
                break;
            }
            case '0': 
            {
                exit(1);
            }
            default: 
            {
                printf("\nEnter Again!");
            }
        }
    } 
    while (choose!='0');
}

char Menu_Display(void)
{
    char type;
    char c;
    printf("\n\t                                MENU\n" );
    printf("\n\t +------------------------------------------------------------------+");
    printf("\n\t |        1. Add Student.                                           |");
    printf("\n\t |        2. Delete Student.                                        |");
    printf("\n\t |        3. Search Student.                                        |");
    printf("\n\t |        4. Sort List.                                             |");
    printf("\n\t |        5. Enter '0' to Exit.                                     |");
    printf("\n\t +------------------------------------------------------------------+\n");
    printf("\tEnter choice: ");
    do 
    {
        printf("\n\tEnter a character = ");
    }
    while ((scanf("%c%c", &type, &c)!=2||c!='\n')&&clean_stdin());
    return type;
}

void Menu(LinkedList_t *list)
{


    char choose;

    printf("\n\tArrayNode[0].pNext is %u\n", ArrayNode[0].pNext);
    
    
    
    do
    {
    /**
     * @Show Menu which shows all options for user and helps user choose option what they want
    */
//        system("cls");
        choose = Menu_Display();
        switch(choose)
        {
            case '1': 
            {   
            	printf("\n\tIn switch case:\n");
        		printf("\n\tArrayNode[0].pNext is %u\n", ArrayNode[0].pNext);
//            	printf("\n\tBefor call LinkedList_AddElement(LinkedList_t *list)\n");
//    			printf("\tlist.head is %u\n",list->head);
//    			printf("\tlist.tail is %u\n",list->tail);
//    			printf("\tlist.freelist is %u\n",list->freelist);
                LinkedList_AddElement(list);
                break;
            }
            case '2': 
            { 
//                LinkedList_DelElement(list);
                break;
            }
            case '3': 
            { 
//                LinkedList_Search(list) ;
                break;
            }
            case '4': 
            { 
//                LinkedList_Sort(list);
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

int main (void)
{
	LinkedList_t *list;
    LinkedList_t memory;
    list = &memory;
	printf("\tBAI TAP STATIC LINKED LIST\n");
	
	printf("\n\tTruoc khi khoi tao:\n");
    printf("\tlist.freelist is %u\n",list->freelist);
    printf("\tlist.head is %u\n",list->head);
    printf("\tlist.tail is %u\n",list->tail);
    printf("\n\tMenu_InitialStaticLinkedList(list);");
    Menu_InitialStaticLinkedList(list);
    printf("\n\tsau khi khoi tao\n");
    printf("\tlist.head is %u\n",list->head);
    printf("\tlist.tail is %u\n",list->tail);
    printf("\tlist.freelist is %u\n",list->freelist);
	


    
    Menu(list);
    return 0;
}
