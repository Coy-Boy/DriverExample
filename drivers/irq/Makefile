KERN_DIR = /home/liuyang/iTop4412_Kernel_3.0

obj-m +=chr_key_irq.o

all:
	 make -C $(KERN_DIR) M=$(PWD) modules
clean:	
	 make -C $(KERN_DIR) M=$(PWD) modules clean
	 rm -rf modules.order
