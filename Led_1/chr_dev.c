#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <asm/io.h>

//LED2
#define CPX2_CON 0x11000100
#define GPX2_SIZE  2

//LED3
#define CPX3_CON 0x11000060
#define GPX3_SIZE  2

//指针存放虚拟地址

volatile unsigned long *gpx2conf; 
volatile unsigned long *gpx2dat;
 
volatile unsigned long *gpx3conf; 
volatile unsigned long *gpx3dat;

static unsigned int dev_major  = 125;
static struct class *devcls;
static struct device *dev;

static int kernel_val = 555;

int chr_dev_open(struct inode *inode,struct file *filp)
{
	printk("******dev %s***********\n",__FUNCTION__);
	return 0;
}
//read(fd,buffer,size);
//fd	 --> filp
//buffer --> buffer
//size   --> count
//必须通过copy_to_user进行传递数据。 

ssize_t chr_dev_read(struct file *filp, char __user *buffer,size_t count,loff_t *fpos)
{
	 
    int ret = copy_to_user(buffer,&kernel_val,count);
    printk("******%s**********\n",__FUNCTION__);
	if(ret > 0) {
		printk(" copy_to_user error  ret:%d\n",ret);	
		return -EFAULT;
	}	
	return 0;
}

ssize_t chr_dev_write(struct file *filp, const char __user *buffer,unsigned int count ,loff_t *fpos)
{
	 
	int value;
	int ret = copy_from_user(&value,buffer,count);
	if(ret > 0) {
		printk(" copy_from_user error  ret:%d\n",ret);	
		return -EFAULT;
	}
	printk("******%s*********\n",__FUNCTION__);
	printk("value = %d\n",value);
	if(value == 48)
	{
	   *gpx2dat |= 0x01;  //led2点灯	
           *gpx3dat |= 0x02;  //led3点灯
	} else {
	    *gpx2dat &= ~(0x01); //led2灭灯
   	    *gpx3dat &= ~(0x02);//led3灭灯
	}
	return 0;
}
int chr_dev_close(struct inode *inode,struct file *filp)
{
	printk("******%s*********\n",__FUNCTION__);
	return 0;
}

const struct file_operations my_fops = {
	.open    = chr_dev_open,
	.read    = chr_dev_read,
	.write 	 = chr_dev_write,
	.release = chr_dev_close,
};


static int __init chr_dev_init(void)
{
 
	//申请设备号
	int ret;
	ret = register_chrdev(dev_major,"chr_dev_test",&my_fops);
	if(ret == 0){
		printk("register ok\n");
	}else{
		printk("register failed\n");
	 
		return -EINVAL;
	}
	//  /dev/chr2 创建类
	devcls = class_create(THIS_MODULE,"chr_dev_test");
	if(devcls != NULL){
		printk("register class ok!\n");
	}else
	{
		printk("register  class faild!\n");
	}
	//创建设备节点 以device_create()最后一个参数为准。
	dev  = device_create(devcls,NULL,MKDEV(dev_major,0),NULL,"chr_dev_cls2"); 
	if(dev != NULL){
		printk("register dev ok\n");
	}else{
		printk("register dev failed\n");
	}
	//LED2 地址映射。  
	gpx2conf = ioremap(CPX2_CON,GPX2_SIZE);
	gpx2dat = gpx2conf + 1;	
	//LED3
	gpx3conf = ioremap(CPX3_CON,GPX3_SIZE);
	gpx3dat = gpx3conf +1;
	//LED2配置
	*gpx2conf &= ~(0xFF);
	*gpx2conf |=  (0x1);
    //LED3 配置
    *gpx3conf &= ~(0xFF);
	*gpx3conf |=  (0x10);
	return 0;
}
static void __exit chr_dev_exit(void)
{
	//一般释放资源
	//和注册时顺序相反
	iounmap(gpx3conf);
	iounmap(gpx2conf);
	device_destroy(devcls,MKDEV(dev_major,0));
	class_destroy(devcls);
	unregister_chrdev(dev_major,"chr_dev_cls2");
	printk("*************chr_dev_exit OK!********\n");
}

module_init(chr_dev_init);
module_exit(chr_dev_exit);
MODULE_LICENSE("GPL");
