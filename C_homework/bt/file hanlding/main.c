#include "Check.h"
#include "Convert.h"
#include <stdint.h>
#include <conio.h>
#include <stdlib.h>
void main (void)
{
    FILE *fp;
    SRecord *srecord;
    uint8_t index = 1;
    printf("\t\t\tOpening file ....");
    fp = fopen("E:\\baitapc1.txt", "r");
    printf("\n\t\t\t==>Starting read SREC file ...\n\n\n");
    while (feof(fp) == 0)              /* feof return != 0 if get end of file and return 0 in another case */
    {
        printf("\t+=========================================================================================================+\n");
        printf("\t|\t\tStarting check line %d\n", index);
        Read_SRecord(srecord, fp);
        printf("\t|\t\tEnd checking line %d\n", index);
        printf("\t+========================================================================================================+\n\n\n\n");
        index ++;
    }
    printf("\t\t\tClosing file ....\n");
    fclose(fp);
}
