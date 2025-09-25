#include <stdio.h>#include <dos.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
struct BOOT { //for Fat16
char jmp[3];
char OEM[8];
int bytes_per_sector;
char sectors_per_cluster;
int reserved;
char FAT_cnt;
int ROOT_size;
int total_sectors;
char media;
int FAT_size
int sectors_per_track;
int head_cnt;
long hidden_sectors;
long total_sectors_long;
char unknown[3];
long serial;
char volume[11];
char FAT_type[8];
char loader[448];
char Mark[2];
};
struct ROOT {
char name[8];
char ext[3];
char attr;
char reserved[10];
char time[2];
char date[2];
int first_cluster;
long size;
};
void main()
{
int drive = 3; // A=0, B=1, C=2, D=3...
//Reading boot sector from disk D
BOOT boot;
int res = absread( driver, 1, 0, &boot);
if(res !=0){
printf("Cannot read boot sector\n);
return;
}
printf("REading disk parameters\n);
printf("-----------------------\n);
printf("Sector size: %d\n", boot.bytes_per_sector);
printf("FAT type:");
int i;
for(i=0; i<8;i++)
printf("%c",boot.FAT_typeturn
//reading FAT16 table from disk D
unsinged int *far = (unsigned int *) malloc (boot.FAT_size*boot.bytes_per_sector);
if (fat ==NULL){
printf("Not enough memory\n);
return;
}
printf("\n\n");
printf( "REading FAT16 parameters\n");
printf( "-------------------------\n");
printf(" FAT size:%d \n",boot.FAT_size);
printf(" Reserved:%d \n",boot.reserved);
res = absread( drive, boot.FAT_size, boot.reserved, fat);
if( res!=0){
printf("Cannot read FAT\n")
return;
}
// printing first 1 FAT cells
for (i=2; i<100; i++)(//first 2 clusters are not used
if(fat ==0 free_count++;
}
printf("\n");
printf("Number of free clusters from first 100 clusters:");
printf("%d\n",free-count);
//printing clusters of a file from cluster n
unsingned int n = 5;
unsingned int cur = n;
printf("Clusters of a file from %u:",n);
While(cur<0xFFF8){
printf("->%u",cur);
cur = fat[cur];
}
//Reading ROOT from disk D
printf("\n\n");
printf("Reading ROOT information:\n");
printf("-------------------------\n");
int num_byte = boot.ROOT_size * 32;//sizeof(ROOT)
ROOT *root = (ROOT *)malloc(num_byte);
if(root == NULL) return;
int num_sector = num_byte / boot.bytes_per_sector;
int root_begin = boot.reserved + boot.FAT_size * boot.FAT_cnt;
res = absread(drive, num_sector, root_begin, (void*)root);
if(res !=0){
printf("\n Cannot read ROOT\n");
return;
}
//printing first 3 items of root
printf("3 first items of root:\");
for(i= 0; i< 3; i++){
if(root.name[0] == ' ') continue;
for(int j=0; j< 8 && root.name[j] !=' '; j++)
printf("\t");
printf("%d \t %ld\n", root.first_cluster, root.size);
}
//find a file with name given in char filename[]
printf("\n");
printf("Clusters belong to file readme:");
int k;
char str[9];
int first_cluster = -1;
for(i=0; i< boot.ROOT_size;i++){
//copy root.name to str to make null-terminated string
for(k=0;k<8 && root.name[k] != ' ';k++)
str[k] = root.name[k];
str[k] = 0;
//comparing
char filename[8];
printf("\n Enter a file name:");
scanf("%s",filename);
if(strcmp(str, filename) == 0){
first_cluster = root.first_cluster;
break;
}
}
//printing clusters belonging to the file
if(first_cluster >=0){
cur = first_cluster;
while(cur< 0xFFF8){
printf("%u", cur);
cur = fat[cur]
}
}
free(root);
free(fat);
getchar();
}