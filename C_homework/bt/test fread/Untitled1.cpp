#include <stdio.h>
#include <string.h>

int main()
{
   FILE *fp;
   char c[] = "Hoc C co ban va nang cao tai QTM !!!";
   char buffer[100];   /* mo file de doc va ghi */
   fp = fopen("baitapc.txt", "w+");   /* Ghi du lieu vao file */
   fwrite(c, strlen(c) + 1, 1, fp);   /* thiet lap vi tri con tro tim kiem ve dau file */
   fseek(fp, SEEK_SET, 0);   /* Doc va hien thi du lieu */
   fread(buffer, strlen(c)+1, 1, fp);
   printf("%s\n", buffer);
   fclose(fp);
   
   return(0);
}
