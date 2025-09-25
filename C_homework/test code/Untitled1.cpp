#include<stdio.h>

#include<string.h>

#define max 100

void XuatMang(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("a[%d] = %c\n",i,a[i]);
    }
}

char CatHoTen(char s[],int a[])
{
    int len=strlen(s);
    int n=0;
    int i;
    for(i=0;i<len;i++)
    {
        if((s[i]>='0') && (s[i]<='9'))
        {
            a[n] = s[i];
            n++;
            int j;
            for(j=i;j<len;j++)
            {
                s[j]=s[j+1];
            }
            s[j+1]='\0';
            i--;
        }
    }
    printf("Chuoi ky tu: %s\n",s);
    XuatMang(a,n);
}

int main()
{
    char s[max];
    int a[max];
    printf("Nhap xau: ");
    gets(s);
    CatHoTen(s,a);
}
