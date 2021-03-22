obj-m+=simple_lkm.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) simple_api.c -o simple_api_test
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm simple_api_test
