//example 2: create 2 threads

#include <pthread.h>

#include <stdio.h>

//parameters to print function

struct char_print_parms

{

            char character; //character to print

            int count; // times to print

};

//Ham xu ly cua thread

//In ky tu ra man hinh, duoc cho boi tham so la mot con tro den cau truc du lieu tren

void* char_print(void* params)

{

            struct char_print_parms* p = (struct char_print_parms*) params; //ep kieu tham so truyen vao

            int i;

            int n = p->count; //Bien chua so lan in ra

            char c=p->character; //Bien chua ma ky tu muon in ra

            for(i=0;i<n;i++)

                        fputc(c,stdout); //Ham in 1 ky tu ra thiet ra chuan

            return NULL;

}

int main(int argc, char** agrv)

{

            pthread_t  thread1_id, thread2_id; //2 bien doi tuong thread

            struct char_print_parms  p1, p2; //2 bien tham so truyen cho ham xu ly cua thread

            //Tao 1 thread in 30000 chu 'x'

            p1.character = 'x';

            p1.count = 30000;

            pthread_create(&thread1_id, NULL, &char_print, &p1);

            //Tao 1 thread khac in ra 20000 chu 'o'

            p2.character = 'o';

            p2.count = 20000;

            pthread_create(&thread2_id, NULL, &char_print, &p2);

            //Dam bao thread1 da ket thuc

            pthread_join(thread1_id, NULL);

            //Dam bao thread2 da ket thuc

            pthread_join(thread2_id, NULL);

            // Now we can safely return.

            return 0;

}