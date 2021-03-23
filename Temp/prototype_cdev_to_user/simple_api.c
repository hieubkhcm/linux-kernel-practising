
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256 //độ dài của chuỗi để ghi xuống và ghi từ kernel
static char receive[BUFFER_LENGTH]; //mảng dùng để chứa chuỗi đọc lại từ kernel

int main(){
   int ret, fd;
   char stringToSend[BUFFER_LENGTH];
   
   printf("Henry's very simple api: send a message to kernel space and read back\n");

   fd = open("/dev/henry_dev", O_RDWR); // Open là một hàm system call trên user space
   // chọn một trong ba lựa chọn cho file O_RDONLY, O_WRONLY, or O_RDWR

   if (fd < 0){//fail trả về trừ một, lỗi ghi vào biến global errno 
      perror("Open the device: FAIL\n");
      return errno; // trả về cho main lỗi của mở fd luôn --> 4debug
   }

   printf("Type in a short string to send to the kernel module:\n");

   scanf("%[^\n]%*c", stringToSend); // %[^\n] : \n ký tự xuống dòng; ^\n all ký tự trự xuống dòng
   // %[^\n] quét all ký tự trừ ký tự xuống dòng, gán cho stringToSend
   // %*c quét một ký tự ở dạng char %c, rồi bỏ luôn ký tự đó *, để làm sạch stdin

   printf("Writing message to the device [%s].\n", stringToSend);

   ret = write(fd, stringToSend, strlen(stringToSend)); // Send the string to the LKM
   //ssize_t write(int fd, const void *buf, size_t count);
   if (ret < 0){ //write() thất bại thì trả về -1, success thì ret số byte ghi vào file
      perror("Failed to write the message to the device.");
      return errno; //trả về cho main lỗi của write() --> 4debug
   }

   printf("Press ENTER to read back from the device...\n");
   getchar();//đợi một ký tự nhập vào // ?vầy có làm dơ stdin không?

   printf("Reading from the device...\n");
   ret = read(fd, receive, BUFFER_LENGTH);        // Read the response from the LKM
   if (ret < 0){
      perror("Failed to read the message from the device.");
      return errno;
   }
   printf("The received message is: [%s]\n", receive);
   printf("End of the program\n");
   return 0;
}
