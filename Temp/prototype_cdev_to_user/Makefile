obj-m += prototype_cdev_to_user.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) simple_api.c -o simple_api_test
	insmod prototype_cdev_to_user.ko
	echo -n "henry" > /dev/henry_dev
	cat /dev/henry_dev
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rmmod prototype_cdev_to_user
