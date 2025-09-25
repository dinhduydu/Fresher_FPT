#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX_SIZE_SSL 10
#define OK 1
#define ERROR 0
typedef int ElemType;

/**
 * A static linked list is an array of structures
 * The next of the first element of the array stores the subscript of the first free node (subscript of the standby list)
 * The next of the last element of the array is used to save the subscript of the first inserted element, which is initially 0
*/
typedef struct{
    ElemType data; //Data domain
    int next; // int cursor; cursor, if 0, no point
}staticLinkList[MAX_SIZE_SSL];

void InitStaticLinkList(staticLinkList slList)
{
    //The next of each element points to the subscript that holds the next element
    for(int i = 0;i < MAX_SIZE_SSL;i++)
    {
        slList[i].next = i+1;
        slList[i].data = -1; // It is used to represent idle nodes when outputting
    }
    //Leave the last node empty
    slList[MAX_SIZE_SSL-1].next = 0;
    //Set the tail node of the spare list to 0
    slList[MAX_SIZE_SSL-2].next = 0;
}
void OutPut(staticLinkList slList)
{
    for(int i = 0;i < MAX_SIZE_SSL;i++)
    {
        printf("i:", i);
		printf("\n\tdata:", slList[i].data);
		printf("\n\t\tnext:",slList[i].next);
    }
}

/*Allocate one unit of memory for the static linked list, i.e. find the first free node*/
int MallocSSL(staticLinkList slList)
{
    //Get the subscript of the first free node (spare list)
    int cursor  = slList[0].next;
    if(cursor)
    {
        slList[0].next = slList[cursor].next;
    }
    return cursor;
}
/*Reclaims the space of the specified subscript in the original array*/
void FreeSSl(staticLinkList slList,int index)
{
    //Reclaim the free node with index as its subscript to the standby linked list
    slList[index].next = slList[0].next;//The node to be released becomes the first node of the standby list, the prefix node of the original first idle node
    slList[index].data = -1;
    slList[0].next = index;//Update the first free node

}
int GetStaticLinkList(staticLinkList slList)
{
    int count = 0;
    int cursor = slList[MAX_SIZE_SSL-1].next;//First element found
    while(cursor)
    {
        //Equivalent to P = P - > next;
        cursor = slList[cursor].next;
        count ++;

    }
    return count;
}

int InsertStaticLinkList(staticLinkList slList,int pos,ElemType element)
{
    if(pos < 1||pos > GetStaticLinkList(slList)+1)
        return ERROR;
    int cursor = MAX_SIZE_SSL - 1;//Get the subscript of the first element
    //Allocated memory
    int newIndex = MallocSSL(slList);
    if(newIndex)
    {
        slList[newIndex].data=element;
        //Find that the prefix node of newIndex is the one before pos
        for(int i = 1;i <= pos-1;i++)
           cursor = slList[cursor].next;
        slList[newIndex].next = slList[cursor].next;
        slList[cursor].next = newIndex;
        return OK;
    }

    return  ERROR;


}
int DeleteStaticLinkList(staticLinkList slList,int pos)
{
    if(pos < 1 || pos > GetStaticLinkList(slList))
        return ERROR;
    int cursor = MAX_SIZE_SSL-1; //Get the subscript of the first node
    for(int i = 1;i < pos-1;i++)//Get the prefix node to delete
    {
        cursor = slList[cursor].next;
    }
    int delIndex = slList[cursor].next;//To delete the subscript of a node
    slList[cursor].next = slList[delIndex].next;
    FreeSSl(slList,delIndex);
    return OK;

}

int main()
{
    staticLinkList slList;
    printf("Initialize static list (empty at this time):\n");
    InitStaticLinkList(slList);
    OutPut(slList);
    InsertStaticLinkList(slList,1,10);
    printf("After inserting an element 10:\n");
    OutPut(slList);
    InsertStaticLinkList(slList,2,20);
    printf("Then insert an element 20:\n");
    OutPut(slList);
    printf("After inserting an element 30:\n");
    InsertStaticLinkList(slList,3,30);
    OutPut(slList);
    printf("Delete element at position 2:\n");
    DeleteStaticLinkList(slList,2);
    OutPut(slList);


    return 0;
}
