obj-m += pid_info.o pid_vminfo.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) sys_tests.c -o tests

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm tests
