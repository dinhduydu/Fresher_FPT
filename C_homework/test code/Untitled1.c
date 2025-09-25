#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
/***********************************Define Struct type************************/
/*Create student's attributes*/
typedef struct Student_Struct_t
{
    char Student_Code[12];
    char Name[30];
    char Account_Name[6];
    float Average_Score;
}Student_t;
/*___________________________________________________________________________*/
/*A Node has always a data item and a "next" pointer to point another node*/
typedef struct Menu_Node_Struct_t
{
    Student_t Menu_Data_Student_Struct;/*a pointer to point  data*/
    struct Menu_Node_Struct_t *next;/*a pointer named next to pointer another node*/
}Node;/*redefine node for use esier*/
/*____________________________________________________________________________*/
/*Head and Tail of Node*/
typedef struct Menu_List_Struct_t
{
    Node *Head;
    Node *Tail;
}List;
/*********************************************************************
*List all Menu_Function 
**********************************************************************/
/*
 *@Function initialize a Node and enter data whose user want
 */
Node* Menu_Init_Node(Student_t content)
{
    Node *temp;/*declare a temp node type of pointer Node*/
    temp = malloc(sizeof(Node));/* Allocate dynamic memory for pointer named temp by malloc()*/
    temp->next = NULL;/*Pointer next point to NULL*/
    /*Next, we assign the temp node's item pointer to the node that the add function passed in*/
    temp->Menu_Data_Student_Struct = content;/* assign value for Node*/
    return temp;/*Return this new node has value yet*/
}
/**
 * @Create List
*/
void Menu_Create_List(List L)
{
    L.Head = NULL;
    L.Tail = NULL;
}

/*
 *@User enter Student data
 */
Student_t Menu_Enter_Student (Student_t x)
{
    printf("\nEnter Student Code: ");  
    gets(x.Student_Code);

    printf("\nEnter Name: ");
    gets(x.Name);  

    printf("\nEnter Account_Name: ");
    gets(x.Account_Name);

    printf("\nEnter Average Score: ");
    scanf("%f", &x.Average_Score);
}
/*Add node to last*/
void Menu_Add_To_Last (List L, Node *p)
{
    if(L.Head==NULL)
    {
        L.Head = p;
        L.Tail = p;
    }
    else
    {
        L.Tail->next = p;
        L.Tail = p;
    }
}
/*Add data to the last*/
void Menu_Enter_Data (List L)
{
    Student_t x;
    char out;   
    printf("\nEnter any key except '0' to continue enter.");
    printf("\nEnter '0' to stop enter.");
    do
    {
        out=getch();
        if(out=='0')
        {
            break;
        }
        Menu_Enter_Student(x);
        Node *p=Menu_Init_Node(x);
        Menu_Add_To_Last(L,p);
    } while (1);
}
void Menu_Print_Data (Student_t x)
{
    printf("\n%u\n%c\n%c\n%c\n%u\n%u\n",x.Student_Code,x.Name,x.Account_Name,x.Average_Score);
}
void Menu_Export (List L)
{
    Node *p;
    p=L.Head;
    while(p!=NULL)
    {
        Menu_Print_Data(p->Menu_Data_Student_Struct);
        p=p->next;
    }
}
void Menu_Max_Average_Score (List L)
{
    Node *p,*max;
    uint8_t count;
    p=L.Head;
    max=p;
    while (p!=NULL)
    {
        if(p->Menu_Data_Student_Struct.Average_Score>max->Menu_Data_Student_Struct.Average_Score)
        {
            max = p; 
            count = 0;
        }
        if(p->Menu_Data_Student_Struct.Average_Score==max->Menu_Data_Student_Struct.Average_Score)
        {
            max=p; count++;
        }
        p=p->next;
    }
    printf("\nStudent has max Average Score is: \n");
    if(count==0)  
    {
        Menu_Print_Data(max->Menu_Data_Student_Struct);
    }
    else
    {
        Node *q=L.Head;
        while (q!=NULL)
        {
            if(q->Menu_Data_Student_Struct.Average_Score==max->Menu_Data_Student_Struct.Average_Score)
            {
                Menu_Print_Data(q->Menu_Data_Student_Struct);
            }
            q=q->next;
        }
    }
}
void Menu_List_Average_Score (List L)
{
    Node *p;
    uint8_t count = 0;
    p=L.Head;
    while (p!=NULL)
    {       
        if(p->Menu_Data_Student_Struct.Average_Score>=5)
        {
          count++;
        }
        p=p->next;
    }
    if(count==0)
    {
        printf("\nThere are no students have Average_Score >=5.");
    }
    else 
    {
        printf("\nHave %d Student have Average_Score >=5.",count);       
    }
}

void Menu_Search (List L)
{
    Node *p;
    uint8_t count = 0;
    char k[20];
    printf("\nEnter students name need to find: ");
    gets(k);
    p=L.Head;
    while (p!=NULL)
    {
        if(strcmp(k,p->Menu_Data_Student_Struct.Name)==0)
        {
            count++;
        }      
        p=p->next;
    }
    if(count!=0)
    {
        printf("\nStudent has been founded: "); output(p->Menu_Data_Student_Struct);
    }
    else printf("\nStudent hasn't been founded.");
}
void Menu_Delete (List L)
{
    Node *p, *q;
    char a[10];
    p=L.Head;
    q=NULL;
    printf("\nEnter Student_Code need to be deleted: ");
    gets(a);
    while (p!=NULL)
    {
        if(strcmp(a, p->Menu_Data_Student_Struct.Student_Code)==0)
        {
            break;    
        }
        else 
        {
            printf("\nThere are no students to be deleted.");
        }
        q=p;
        p=p->next;
    }
    if(q!=NULL)
    {
        if(p!=NULL)
        {
            q->next=p->next;
            Menu_Delete(p);
            if(p==L.Tail)
            {
                L.Tail=q;
            }
            Menu_Delete(p);
        }
    }
    else
    {
        L.Head=p->next;
        Menu_Delete(p);
        if(L.Head==NULL)
        {
            L.Tail=NULL;
        }
    }
}
void selectionsort (List L)
{
    Node *p,*q,*min;
    p=L.Head;
    Student_t temp;
    while (p!=L.Tail)
    {
        min=p;
        q=p->next;
        while (q!=NULL)
        {
            if(q->Menu_Data_Student_Struct.Average_Score<min->Menu_Data_Student_Struct.Average_Score)
            {
                min=q;
            }
            q=q->next;
        }
        temp=p->Menu_Data_Student_Struct;
        p->Menu_Data_Student_Struct=min->Menu_Data_Student_Struct;
        min->Menu_Data_Student_Struct=temp;
        p=p->next;
    }
}
void menu()
{
    List L;
    Node *p,*q;
    Student_t x;
    char choose;
    CreateList(L);
    do
    {
    /**
     * @Show Menu which shows all options for user and helps user choose option what they want
    */
        printf("\n\t                  MENU\n");
        printf("\t\t +------------------------------------------------------------------+\n");
        printf("\n\t |        1. Enter list.                                            |");
        printf("\n\t |        2. Print list.                                            |");
        printf("\n\t |        3. List of Students have Average_Score highest.           |");
        printf("\n\t |        4. List of Students have Average_Score >=5.               |");
        printf("\n\t |        5. Search Student.                                        |");
        printf("\n\t |        6. Delete Student.                                        |");
        printf("\n\t |        7. Sort List.                                             |");
        printf("\n\t |        8. Insert List.                                           |");
        printf("\n\t |        9. Enter '0' to Exit.                                     |");
        printf("\t\t +------------------------------------------------------------------+\n");
        printf("\tEnter choice: ");
        choose=getch();
        switch(choose)
        {
            case '1': 
            { 
                Menu_Enter_Data(L); 
                break;
            }
            case '2': 
            { 
                Menu_Export(L); 
                break;
            }
            case '3': 
            { 
                Menu_Max_Average_Score(L); 
                break;
            }
            case '4': 
            { 
                Menu_List_Average_Score(L); 
                break;
            }
            case '5': 
            { 
                Menu_Search(L); 
                break;
            }
            case '6': 
            { 
                Menu_List_Average_Score(L); 
                printf("\nList After deleted: "); 
                Menu_Export(L); 
                break;}
            case '7': 
            { 
                selectionsort(L);
                printf("\nList After sorted: "); 
                Menu_Export(L); 
                break;
            }
            case '8':
            {
                Student_t add;
                printf("\nEnter Data of Student need to be added: ");
                Menu_Enter_Student(add);
                Node *t= Menu_Init_Node(add);
                Menu_Add_To_Last(L,t);
                selectionsort(L);
                printf("\nList After added :");
                Menu_Export(L);
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
