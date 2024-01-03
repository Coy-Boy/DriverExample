#include <linux/module.h>
#include <linux/init.h>


#include <asm/uaccess.h>
#include <asm/io.h>


static int kernel_dev = 555;
int chr_dev_open(struct inode * inode,struct file *filp)
{
  printk("****%s*****",__FUNCTION__);
  return 0;
}
ssize_t chr_dev_read(struct file *filp, char __user *buffer,size_t count,loff_t *fpos)
{
	printk("******%s************",__FUNCTION__);
    int ret = copy_to_user(buffer,&kernel_val,count);
	if(ret > 0){
		printk(" copy_to_user error  ret:%d\n",ret);	
		return -EFAULT;
	}	
	return 0;
}

ssize_t chr_dev_write(struct file *filp, const char __user *buffer,size_t count ,loff_t *fpos)
{
	//printk("******%s************",__FUNCTION__);
	int value;
	int ret = copy_from_user(value,mbuffer,count);
	if(ret > 0){
		printk(" copy_from_user error  ret:%d\n",ret);	
		return -EFAULT;
	}
	
	printk("__KEY___: value = %d\n",value);
	if(value){
		*gpx2dat |= (1<<7);  //点灯
	}else{
	 *gpx2dat &= ~(1<<7);
	}
	
	
	return 0;
}
int chr_dev_close(struct inode *inode,struct file *filp)
{
	printk("******%s************",__FUNCTION__);
	return 0;
}

const struct file_operations my_fops = {
	.open  = chr_dev_open,
	.read  = chr_dev_read,
	.write = chr_dev_write,
	.release = chr_dev_close,
};

static int __init chr_dev_init(void)
{
  printk("ch_dev_init\n");
  return 0;
}

static void __exit chr_dev_exit(void)
{
   printk("chr_dev_exit\n");
}




moudule_init(chr_dev_init);
moudule_exit(chr_dev_exit);


MODULE_LICENSE("GPL");
