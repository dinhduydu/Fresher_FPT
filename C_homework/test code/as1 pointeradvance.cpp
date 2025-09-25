#include <stdio.h> 

int main() 

{ 
    char *c; /* pointer point to char */
    char **s; /* s is a pointer to pointer to char. sizeof(s) == sizeof(void*) */
    char foo[] = "Hello World"; 
    s = (char**)foo; /* type of foo = char(*)[12] --> casting char** */
    printf("s is %s\n",(char *)s); 
    c = (char*)&s[0]; /* s is type of char** -> casting char* */
    printf("s[0] is %c\n", *c); 
    return(0); 
}


//{
//    printf("To Check ptrs \t");
//    int var[3]={10,20,30};
//    int *ptr,i;
//    ptr=var;
//    for(i=0;i<3;i++)
//    {
//       printf("Address is %d \t", ptr);
//       printf("Value is %d \t", *ptr);
//       ptr++;
//    }
//    ptr=(int*)&var;
//    for(i=0;i<3;i++)
//    {
//       printf("Address is %d \t", &ptr[i]);
//       printf("Value is %d \t", ptr[i]);
//    }
//}
