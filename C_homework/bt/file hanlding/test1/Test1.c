#include <stdio.h>
#include <stdlib.h>
//
//int main ()
//{
//	FILE *fp;
//	
//	fp = fopen("E:\\examples.text","w");
//	
//	if (fp == NULL)
//	{
//		printf("Error!");
//		exit(1);
//	}
//	
//	fputs("Learning about File Handling", fp);  /* Writes the string s to the stream */
//	fputs("\nLearning about File Handling", fp);
//	fclose(fp); /* close file  */
//	
//	return (0);
//}

//int main ()
//{
//	FILE *fptr;
//	int id;
//	char name[30];
//	int salary;
//	
//	fptr = fopen("E:\\Infor.txt", "w+");
//	if (fptr == NULL)
//	{
//		printf("File khong ton tai hoac file ko mo duoc.\n");
//		exit(1);
//	}
//	
//	printf("Nhap id: ");
//	scanf("%d", &id);
//	fprintf(fptr, "Id = %d\n", id);
//	
//	printf("Nhap name: ");
//	scanf("%s", name);
//	fprintf(fptr, "Name = %s\n", name);
//	
//	fclose(fptr);
//	return 0;
//}


/* VI DU VE HAM FSCANF*/
//
//int main ()
//{
//	char str1[10], str2[10], str3[10];
//	int year;
//	FILE *fp;
//	
//	fp = fopen("E:\\baitapc.txt","w+");
//	fputs("Nam nay la 2022", fp);
//	
//	rewind(fp);
//	
//	fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
//	
//	printf("Doc chuoi 1: |%s|\n", str1);
//	printf("Doc chuoi 2: |%s|\n", str2);
//	printf("Doc chuoi 3: |%s|\n", str3);
//	printf("Doc so nguyen: |%d|\n", year);
//	
//	fclose(fp);
//}


int main ()
{
	int input_char;
	FILE *my_stream;
	char my_filename[] = "E:\\example.txt";
	int eof_status, error_status;
	
	printf("Opening file ...\n");
	my_stream = fopen (my_filename, "w+");
	fprintf(my_stream, "ABCDEFGHIJKLMOPORSTUVWXYZ");
	
	/* Seeking poisition 25 = 'Z' */
	fseek(my_stream, 25, SEEK_SET);
	input_char = getc(my_stream);
	printf("Character = '%c'.\n", input_char);
	
	/* check EOF */
	eof_status = feof(my_stream);
	printf("feof returns %d.\n", eof_status);
	
	/* check error */
	error_status = ferror(my_stream);
	printf("ferror returns %d.\n\n", error_status);
	
	fclose (my_stream);
	return 0;
	
}
