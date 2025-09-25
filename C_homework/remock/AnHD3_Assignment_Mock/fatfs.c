/******************************************************************************
 * Include
 ******************************************************************************/
#include <stdio.h>
#include "fatfs.h"

/******************************************************************************
 * Code
 ******************************************************************************/
 
Rootdirectory rootdirectory;
int count = 0;


int read_num_entry(FILE *fptr, uint8_t *buff, int *p)
{
    fseek(fptr, (19 * byte_sector), SEEK_SET);
    fread(buff, 1, 512, fptr);
    int arr[16];
    int x = 0;
	int i = 0;
    for (i = 0; i < 512; i++)
    {
        if (((i % byte_entry) - check_sub_entry == 0 && buff[i] == 0x0F))
        {
            x = i / byte_entry;

            rootdirectory.arr[x] = 1;
        }
        else if ((i % byte_entry) - check_sub_entry == 0 && buff[i] == 0x10)
        {
            int b = 0;
            b = i / byte_entry;
            rootdirectory.arr[b] = 2;
        }
        else
        {
            int c = 0;
            c = (i / byte_entry);
            arr[c] = 0;
        }
    }
    for (i = 0; i < 16; i++)
    {
        *(p + i) = rootdirectory.arr[i];
    }

    return 0;
}

void read_file(FILE *fptr, uint8_t *buff, int num_entry)
{
    count++;
    int b;
    int hour;
    int minute;
    int second;
    int day;
    int month;
    int year;

    /*NOTE: read name file*/
    printf("%2d\t", count);
    fseek(fptr, (19 * byte_sector) + (num_entry * byte_entry), SEEK_SET);
    fread(buff, 11, 1, fptr);

    for (int i = 0; i < 11; i++)
    {
        printf("%c", buff[i]);
    }

/*NOTE: read hour/minute/second
 * Get 3 high bit of byte 22 AND ( get 3 low bit of byte 23 AND move to right 3 bit)
 * Get 5 low bit of byte 22
 */
    fseek(fptr, (19 * byte_sector) + (byte_entry * num_entry) + 22, SEEK_SET);
    fread(buff, 2, 1, fptr);
    rootdirectory.time[0] = buff[1];
    rootdirectory.time[1] = buff[0];
    hour = buff[1] >> 3;
    minute = (buff[0] >> 5) | ((buff[1] & 7) << 3); 
    second = buff[0] & 0x1F;                        
    second = second * 2;
    printf("\t%02d:%02d:%02d", hour, minute, second);

    
/*NOTE: read day/month/year
 * get 3 high bit of byte 24 AND( 1 low bit of byte 25 and move to right 3 bit)
 * get 5 low bit of byte 25
 */
    fseek(fptr, (19 * byte_sector) + (byte_entry * num_entry) + 24, SEEK_SET);
    fread(buff, 2, 1, fptr);
    rootdirectory.time[0] = buff[1];
    rootdirectory.time[1] = buff[0];
    year = buff[1] >> 1;
    month = (buff[0] >> 5) | ((buff[1] & 1) << 3); /*lay 3 bit cao cua byte 24, va( 1 bit thap cua byte 25 va dich sang phai 3 bit)*/
    day = buff[0] & 0x1F;                          /*lay 5 bit thap cua byte 22*/
    printf(" %02d/%02d/%04d", day, month, year + 1980);

/*NOTE: read type of file*/
    fseek(fptr, (19 * byte_sector) + (byte_entry * num_entry) + 11, SEEK_SET);
    fread(buff, 1, 1, fptr);
    rootdirectory.type[0] = buff[0];
    if (rootdirectory.type[0] == 0x10)
    {
        printf("\tFile folder\t");
    }
    else
    {
        printf("\tText document\t");
    }

/*NOTE: read size of file*/
    fseek(fptr, (19 * byte_sector) + (byte_entry * num_entry) + 28, SEEK_SET);
    fread(buff, 1, 4, fptr);
    for (int i = 3; i >= 0; i--)
    {
        int x = 0;
        b = (buff[i] << 8 * i | b);
    }
    rootdirectory.size = b;
    if (rootdirectory.type[0] == 0x10)
    {
        printf("\n");
    }
    else
    {
        printf("1kB\n");
    }
}

int first_cluster(FILE *fptr, uint8_t *buff, int num_entry)
{
    int temp;
    fseek(fptr, (sector_boot + sector_fat * 2) * byte_sector + byte_entry * num_entry + start_cluster_, SEEK_SET);
    fread(buff, 2, 1, fptr);
    temp = ((buff[1] << 8) | buff[0]);
    return temp;
}

void display_data(FILE *fptr, uint8_t *buff, int num_entry)
{
    int a = 0;
    /* = boot_sector size + fatsize + root_directory_size + num_emtry  - 2*/
    int num_entry_data = 33 + num_entry - 2;
    fseek(fptr, num_entry_data * byte_sector, SEEK_SET);
    fread(buff, byte_sector, 1, fptr);
    printf("%s", buff);
}

void read_file_2(FILE *fptr, uint8_t *buff, int num_entry, int start_cluster)
{
    count =0;
    int i;
    int position = (sector_boot + sector_fat * 2) + 14 + start_cluster - 2; /* (19 + 14 - 2) start_cluster <=>  start_cluster + 31 */
    count++;
    int b;
    int hour;
    int minute;
    int second;
    int day;
    int month;
    int year;

    fseek(fptr, (position * byte_sector), SEEK_SET);
    fread(buff, 64, 1, fptr);
    if (buff[0] == 0x2E && buff[32] == 0x2E && buff[64] == 0x00)
    {
        printf("Folder empty\n");
    }
    else
    {
        /*NOTE: read name file*/
        fseek(fptr, (position * byte_sector) + (num_entry * byte_entry), SEEK_SET);
        fread(buff, 11, 1, fptr);
        for (int i = 0; i < 11; i++)
        {
            printf("%c", buff[i]);
        }
        
        /*NOTE: read hour/minute/second */
        fseek(fptr, (position * byte_sector) + (byte_entry * num_entry) + 22, SEEK_SET);
        fread(buff, 2, 1, fptr);
        rootdirectory.time[0] = buff[1];
        rootdirectory.time[1] = buff[0];
        hour = buff[1] >> 3;
        minute = (buff[0] >> 5) | ((buff[1] & 7) << 3); 
        second = buff[0] & 0x1F;                        
        second = second * 2;
        printf("\t%02d:%02d:%02d", hour, minute, second);

        /*NOTE: read day/month/year*/
        fseek(fptr, (position * byte_sector) + (byte_entry * num_entry) + 24, SEEK_SET);
        fread(buff, 2, 1, fptr);
        rootdirectory.time[0] = buff[1];
        rootdirectory.time[1] = buff[0];
        year = buff[1] >> 1;
        month = (buff[0] >> 5) | ((buff[1] & 1) << 3); 
        day = buff[0] & 0x1F;                         
        printf(" %02d/%02d/%04d", day, month, year + 1980);

        /*NOTE: read type of file*/
        fseek(fptr, (position * byte_sector) + (byte_entry * num_entry) + 11, SEEK_SET);
        fread(buff, 1, 1, fptr);
        rootdirectory.type[0] = buff[0];
        if (rootdirectory.type[0] == 0x10)
        {
            printf("\tFile folder\t");
        }
        else
        {
            printf("\tText document\t");
        }

        /*NOTE: read size of file*/
        fseek(fptr, (position * byte_sector) + (byte_entry * num_entry) + 28, SEEK_SET);
        fread(buff, 1, 4, fptr);
        for (int i = 3; i >= 0; i--)
        {
            int x = 0;
            b = (buff[i] << 8 * i | b);
        }
        rootdirectory.size = b;
        if (rootdirectory.type[0] == 0x10)
        {
            printf("\n");
        }
        else
        {
            printf("1kB\n");
        }
    }
}

