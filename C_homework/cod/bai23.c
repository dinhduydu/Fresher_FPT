#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/* Dinh nghia cau truc luu tru thong tin sinh vien.*/
struct SinhVien
{
   char Ma[8];
   char Ten[31];
   char Lop[7];
   float Diem;
};
 
/*Khai bao mang de luu tru danh sach sinh vien.*/
struct SinhVien sv[50];
int n = 0; // Bien luu tru so sinh vien hien tai.
 
// Ham thuc hien in Menu.
int HienThiMenu()
{
   	system("cls");
   	printf("CT QUAN LY DAY SO BANG MANG\n");
   	printf("=====================\n");
	printf("HUONG DAN SU DUNG\n");
	printf("=====================\n");
 	printf("Mang gom 100 phan tu ");
   	printf("1. Nhap 'c' de tao mang so nguyen (Neu da co mang thi clear data cua mang cu)\n");
   	printf("2. Nhap 'p' de in day (Neu day chua co gia tri thi bao trong.)\n");
   	printf("3. Nhap 'i' de them 1 phan tu vao day\n");
   	printf("4. Nhap 'd' de xoa 1 phan tu tai vi tri thu k (Neu vi tri k khong chua gia tri thi bao ko co phan tu k)\n");
	printf("5. Nhap 's' de sap xep theo day so theo chieu tang dan.\n");
   	printf("6. Nhap 'x' de sap xep day so theo chieu giam dan.\n");
   	printf("7. Nhap 't' de tim kiem 1 so x co trong day khong (x nhap tu ban phim)?");
   	printf("8. Nhap 'e' de thoat chuong trinh.");
   	printf("Ban chon: ");
   	char chon;
   	scanf("%c",&chon);
   	return chon;
}
 
/*Ham tao mang so nguyen*/
void TaoMangSoNguyen()()
{
	printf("\n----------------------\n");
   	printf("NHAP MANG SO NGUYEN\n");
   	printf("=====================\n");
 
   /*Nhap mang so nguyen*/
   do
   {
      printf("Mang thu %d:\n",n+1);
      printf("\tMa: ");
      fflush(stdin);
      gets(sv[n].Ma);
      // Neu Ma la khoang trang thi dung ko nhap tiep.
      // Ma la khoang trang neu do dai cua Ma la 0.
      if (strlen(sv[n].Ma)==0)
      {
        break;
      }
      printf("\tTen: ");
      fflush(stdin);
      gets(sv[n].Ten);
      printf("\tLop: ");
      fflush(stdin);
      gets(sv[n].Lop);
      printf("\tDiem: ");
      scanf("%f",&sv[n].Diem);
      n++;
   }
   while (1==1);
}
 
// Ham in danh sach sinh vien.
void InDanhSachSinhVien()
{
    printf("\n-----------------\n");
   printf("DANH SACH SINH VIEN\n");
   printf("-------------------\n");
 
   printf("%-14s %-25s %-8s  Diem\n","Ma sinh vien", "Ten sinh vien", "Lop");
   for (int i=0; i<n; i++)
   {
        printf("%-14s %-25s %-8s  %.1f\n",sv[i].Ma, sv[i].Ten, sv[i].Lop, sv[i].Diem);
   }
 
   printf("\nBam ENTER de tiep tuc");
   getch();
}
 
// Ham tim kiem.
void TimKiem()
{
    printf("\n----------------\n");
   printf("TIM KIEM THONG TIN\n");
   printf("------------------\n");
   printf("Kieu tim kiem (0 - Tim kiem theo ma, 1 - Tim kiem theo ten\n");
   printf("Ban chon: ");
   int chon;
   scanf("%d",&chon);
 
   if (chon==0)
   {
    char Ma[7];
      printf("Ma: ");
      fflush(stdin);
      gets(Ma);
 
      struct SinhVien svTimThay;
      int timThay = 0;
      for (int i=0; i<n; i++)
      {
        // Neu Ma nhap trung voi ma cua sinh vien thu i
         // -> Tim thay.
         if (strcmp(Ma,sv[i].Ma)==0)
            {
                svTimThay = sv[i];
            timThay = 1;
            break;
         }
      }
 
      printf("Ket qua tim kiem:\n");
      if (timThay==0)
      {
        printf("Khong tim thay sinh vien nao co ma la [%s]\n",Ma);
      }
      else
      {
            printf("%-14s %-25s %-8s  Diem\n","Ma sinh vien", "Ten sinh vien", "Lop");
            printf("%-14s %-25s %-8s  %.1f\n",svTimThay.Ma, svTimThay.Ten, svTimThay.Lop, svTimThay.Diem);
      }
   }
   else
   {
    char Ten[31];
    printf("Ten: ");
      fflush(stdin);
      gets(Ten);
 
      int timThay = 0;
      printf("Ket qua tim kiem:\n");
      printf("%-14s %-25s %-8s  Diem\n","Ma sinh vien", "Ten sinh vien", "Lop");
      for (int i=0; i<n; i++)
      {
        // Neu Ten nhap trung voi Ten cua sinh vien thu i
         // -> Tim thay.
         if (strcmp(Ten,sv[i].Ten)==0)
            {
            timThay = 1;
            printf("%-14s %-25s %-8s  %.1f\n",sv[i].Ma, sv[i].Ten, sv[i].Lop, sv[i].Diem);
         }
      }
 
      if (timThay==0)
      {
        printf("Khong tim thay sinh vien nao co ten la [%s]\n",Ten);
      }
   }
 
   printf("\nBam ENTER de tiep tuc");
   getch();
}
 
// Ham in danh sach sinh vien thi do.
void InDanhSachSinhVienThiDo()
{
    printf("\n------------------------\n");
   printf("DANH SACH SINH VIEN THI DO\n");
   printf("--------------------------\n");
 
   printf("%-14s %-25s %-8s  Diem\n","Ma sinh vien", "Ten sinh vien", "Lop");
   for (int i=0; i<n; i++)
   {
    if (sv[i].Diem>=10)
      {
            printf("%-14s %-25s %-8s  %.1f\n",sv[i].Ma, sv[i].Ten, sv[i].Lop, sv[i].Diem);
      }
   }
 
   printf("\nBam ENTER de tiep tuc");
   getch();
}

void main()
{
    int chon;
   do
   {
    chon = HienThiMenu();
    switch (chon)
    {
        case c:
            TaoMangSoNguyen();
            break;
        case p:
            InDay();
            break;
        case i:
            ThemMotPhanTuVaoDay
            break;
        case d:
            XoaMotPhanTuTaiViTriK();
            break;
        case s:
        	SapXepTheoChieuTang();
        	break;
        case x:
        	SapXepTheoChieuGiam();
        	break;
        case t:
        	TimKiem();
        	break;
        case e:
        	ThoatChuongTrinh();
        	break;
      }
    }
   while (chon!=c || chon!=p|| chon!=i || chon!=d || chon !=s || chon!=x || chon!=t || chon!=e);
}
