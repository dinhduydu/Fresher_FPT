
        +----+------+--------------+----------+----------------------------+----------+
        | S  | Type |  Byte Count  |  Address |             Data           | CheckSum |
        +----+------+--------------+----------+----------------------------+----------+

 S + Type: a char[2] field. these character the typde of record (S0, S1, S2, S3, S5, S6, S7, S8, S9)
    
ByteCount: a char[2] field. These characters when paired and interpreted as a big-endian hexadecimal integer, display 
the count of remaining character pairs in the record.

Address: a char[4,6, or 8] field. The length of the field depends on number of bytes necessary to hold address. 
2-byte address uses 4 characters, a 3 byte address uses 6 characters, and 4-byte address uses 8 characters.

Data: a char[0-64] field (32 bytes)

CheckSum: a char[2] field






Viết chương trình parse file SREC

Yêu cầu: 
    Kiểm tra định dạng (kí tự không phải của hexa) 
tức là có 1 function check hexa tức là tự nhiên có 1 số không phải số hexa là sai rồi, check các ký tự nằm ngoài hexa
    
check sum và check byte count

check line là đếm s5 hay s6

check ký tự S đầu tiên, xem bắt đầu 1 line record có S đầu tiên ko
nhỡ là A C P thì sao
nên là cần có function để check ký tự đầu tiên 

    và checksum, byte count của từng dòng, kiểm tra S5 S6 và in ra đầy đủ các lỗi như sau:
        - lineNumber summary(lỗi gì)

        Nếu không lỗi in ra màn hình các thông tin (của S1/S2/S3) như sau:
        - địa chỉ
        - dữ liệu


        cần có hàm check Type; check kiểu, tức là khi đọc S0 thì mình biết nó đọc cái gì 
        s2 s3 thì dựa vào thằng này
        rơi vào s5 thì biết là đếm cái gì
        vì chức năng của các cái này khác nhau
        s5 ko có data nên là với các S khác nhau thì xử lý khác nhau
        nên là có function để check type của nó
        nghĩa là đã đọc S1 thì đọc S rồi thì đọc tiếp S kết thúc của nó là 1 hay là 9, cái đó thì nằm trong check s rồi
        néu nhảy vào S tương ứng 
        check kết thức nằm ở trong check type
        với các type là s1 s2 s3 thì mình có các cách xử lý khác nhau 

        cần có function đi kèm là uint8_t convertDec (uint8_t Num) sẽ làm nhiệm vụ chuyển đổi cho mình và truyền vào NUm là ký tự 1
        thực chất giá trị là 49
        làm sao để sau output của nó nhả ra giá trị 1

        làm sao để đếm được và cộng được l

        convert number và ghép thành 1 byte --> 2 function


        enum error_type 
        {
            OK,
            ERROR_S,
            ERROR_HEXA,
            ERROR_LINE,
            ERROR_BYTE_COUNT,
            ERROR_CHECK_SUM
        };

        error_type check_S();
        error_type check_hexa();
        error_type check_line();

        L1;
        error_type error_check_S();
        error_type error_check_Hexa();
        error_type error_check_line();

        error_check_S = check_s(L1);
        error_check_hexa = check_hexa(L1);
        error_check_line = check_line(L1);


file text là file mà con người đọc được
binary là 0101 bị mã hoá rồi

byte count đếm từ address đến checksum