// chương trình C dùng để tìm ra số lớn nhất trong 3 số
// dùng argc: argument count và argv argument value để parse vào cho main()
#include <stdio.h> 
#include <stdlib.h>
  
// Cách truyền đối số cho main như sau ./main_with_arg arg1 arg2 arg3 
int main(int argc, char *argv[])  
{ 
    int a, b, c; 
  
    // argc sẽ bằng số arg truyền vào, bao gồm cả exe, 
    // ví dụ filename arg1 arg2 arg3 thì số argc sẽ là 4
    if (argc < 4 || argc > 5) //code này chỗ lớn hơn 5 có vẻ như sai
    { 
        printf("enter 4 arguments only eg.\"filename arg1 arg2 arg3!!\""); 
        return 0; // thoát khỏi hàm main, trả giá trị về là 0 
    } // 0: nghĩa là hàm chạy thành công, chỉ có đối số sai số lượng thôi
  
    // do nạp vào là char nên cần convert về integer 
    // using function atoi(ascii character)  
    // atoi: ASCII to Integer nằm trong thư viện stdlib.h
    a = atoi(argv[1]);  
    b = atoi(argv[2]); 
    c = atoi(argv[3]); 
  
    // Checking if all the numbers are positive of not 
    if (a < 0 || b < 0 || c < 0)  
    { 
        printf("enter only positive values in arguments !!"); 
        return 1; 
    } // return 1 chắc lâ để phân biệt với các mã lỗi khác
  
    // mấy bước xàm xí này có cần thiểt không vậy? 
    if (!(a != b && b != c && a != c))  
    { 
        printf("please enter three different value "); 
        return 2; 
    } // ban đầu là return 1 ==> chuyển thành return 2 cho phân biệt với lỗi trên
    else
    { 
        // Checking condition for "a" to be largest 
        if (a > b && a > c)              
            printf("%d is largest", a); 
  
        // Checking condition for "b" to be largest     
        else if (b > c && b > a)  
            printf ("%d is largest", b); 
  
        // Checking condition for "c" to be largest.. 
        else if (c > a && c > b)  
            printf("%d is largest ",c); 
    } 
    return 0; // bên trên return 0, bên dưới cũng return 0, dễ hiểu lầm quá đi mà
} 