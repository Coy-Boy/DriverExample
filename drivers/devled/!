KERN_DIR = /home/liuyang/itop4412_bsp

obj-m +=chr_dev.o

all:
	 make -C $(KERN_DIR) M=$(PWD) modules
clean:	
	 make -C $(KERN_DIR) M=$(PWD) modules clean
	 rm -rf modules.order
