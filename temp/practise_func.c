#include <stdio.h>


int a_plus_b(int , int );


int main(void)
{
	int a1=2, b1=3;
	int c;
	c = a_plus_b(a1,b1);
	printf("c = %d\n",c);
	return 0;
}

int a_plus_b (int a, int b)
{
	return (a+b);
}
