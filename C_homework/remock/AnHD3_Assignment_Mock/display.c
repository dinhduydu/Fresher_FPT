#include "app.h"

void menu()
{
    printf("\n\n        FILESYSTEM TYPE            FAT12");
    printf("\n         ------------------------------------------------\n");
    printf("\nSTT    Name           Date modified        Type        Size");
    printf("\n-----------------------------------------------------------------------\n");
}

void display(void)
{
	uint32_t check_sub[16];
    uint32_t num_sub[16];
    int choice = 8;  
    char x;
    FILE *fptr;
//    fptr = fopen("C:\\Users\\MyPC\\Documents\\LTHDT\\Fresher\\Mock\\img\\img\\floppy.img", "rb");
    char addressFile []= "";
    
    printf("Input address file:\n ");
    printf("(Ex: floppy.img)\t");
    gets(addressFile);
    fptr = fopen(addressFile,"r");
    
    if (fptr == NULL)
    {
        printf("Failed to open file");
    }
    else
    {
        menu();

        read_num_entry(fptr, buff, check_sub);
int i = 0;
        for (i = 0; i < 16; i++)
        {
            if (check_sub[i] == 1)
            {
                read_file(fptr, buff, i + 1);
            }
            else if (check_sub[i] == 2)
            {
                read_file(fptr, buff, i);
            }
        }

        do
        {
            uint32_t a, b, c, d, e, f, g;
            int v;
            int pos_sec;
            int num_pos_sec;
            printf("\nchoice file or folder: ");
            scanf("%c", &x);
            fflush(stdin);
            switch (x)
            {
            case '1':
            {
                a = first_cluster(fptr, buff, 1); // a=3
                display_data(fptr, sub_buff, a);  // tro toi sector 34
                break;
            }
            case '2':
            {
                b = first_cluster(fptr, buff, 3);
                display_data(fptr, sub_buff, b);
                break;
            }
            case '3':
            {
                c = first_cluster(fptr, buff, 5);
                display_data(fptr, sub_buff, c);
                break;
            }
            case '4':
            {
                d = first_cluster(fptr, buff, 7);
                display_data(fptr, sub_buff, d);
                break;
            }
            case '5':
            {
                e = first_cluster(fptr, buff, 8);
                printf("\n");
                
                read_file_2(fptr, buff, 2, e);
                printf("\n");
                //read_num_sub_entry(fptr,buff,num_sub,e);

                break;
            }
            case '6':
            {
                f = first_cluster(fptr, buff, 9);
                printf("\n 1\t");
                read_file_2(fptr, buff, 2, f);
                printf("\n 2\t");
                read_file_2(fptr, buff, 3, f);
                printf("\n 3\t");
                read_file_2(fptr, buff, 4, f);
                while(choice!=0)
                {
                    printf("\ndoc file trong DOC : ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                        case 1:
                        display_data(fptr, sub_buff,8 );
                        break; 
                        case 2:
                        display_data(fptr, sub_buff,747 ); //02 EB = 747
                        break;
                        case 3:    
                        read_file_2(fptr, buff, 2, 1265);    
                        break;
                    }         
               }
                  break;
            }
            case '7':
            {
                f = first_cluster(fptr, buff, 10); /*f is a frist cluster of PIC folder (entry 10 of root directory) */ 
                printf("\n 1\t");
                read_file_2(fptr, buff, 2, f);
                printf("\n 2\t");
                read_file_2(fptr, buff, 3, f);
                 while(choice!=0)
                {
                    printf("\ndoc file trong PIC : ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                        case 1:
                        display_data(fptr, sub_buff,1260 ); // first cluster cua entry 2 cua sub_directory.
                        break; 
                        case 2:
                        display_data(fptr, sub_buff,1262 );  // first cluster cua entry 3 cua sub_directory.
                        break;    
                    }
               }
                break;
            }
            }
        } while (x != 10);
    }
    fclose(fptr);
}
