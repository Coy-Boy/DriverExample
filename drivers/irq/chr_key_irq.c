#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <asm/io.h>

#include <linux/of_irq.h>
#include <linux/of.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
/*
#define __IRQT_FALEDGE IRQ_TYPE_EDGE_FALLING
#define __IRQT_RISEDGE IRQ_TYPE_EDGE_RISING
#define __IRQT_LOWLVL IRQ_TYPE_LEVEL_LOW
#define __IRQT_HIGHLVL IRQ_TYPE_LEVEL_HIGH
#define IRQT_NOEDGE (0)
#define IRQT_RISING (__IRQT_RISEDGE)
#define IRQT_FALLING (__IRQT_FALEDGE)
#define IRQT_BOTHEDGE (__IRQT_RISEDGE|__IRQT_FALEDGE)
#define IRQT_LOW (__IRQT_LOWLVL)
#define IRQT_HIGH (__IRQT_HIGHLVL)
#define IRQT_PROBE IRQ_TYPE_PROBE
*/


/*
    GPIO 学习 按键获取键值-----中断方式
    标准字符驱动编写
*/
//GPX1—2
//IRQ_EINT(10)

#define BACK_HOME_CONFIG_BASE 0x11000C20

struct key_drv{
    int major;
    struct class  *third_drv_cls;
    struct device *third_drv_dev;
    unsigned long *gpfcon;
    unsigned long *gpfdat;

};
static struct key_drv *key_chrdrv;
static  char back_value = 0;
//static DECLARE_WAIT_QUEUE_HEAD(button_waitq); /*注册一个等待队列*/

unsigned int ev_press;
/*
    按键中断处理函数
*/
/*static irqturn_t buttons_irq(int irq,void *dev_id)
{
    return IRQ_HANDLER;
}*/
static irqreturn_t button_irq(int irq,void * dev_id)
{
  unsigned long value;
  value = *(key_chrdrv->gpfdat);
  printk("value:%ld\n",value);
  printk("%s:%d\n",__func__,__LINE__);
  if((value>>2 & 0x01) == 1)
      back_value = 1;
  else
      back_value = 0;
  //wake_up_interruptible(&button_waitq);
  //ev_press = 1;
  return IRQ_HANDLED;
}


static int key_drv_open(struct inode *inode ,struct file *file)
{
    int ret;
    printk("%s:%d\n",__func__,__LINE__);
    ret = request_irq(IRQ_EINT10,button_irq,IRQ_TYPE_EDGE_FALLING|SA_TRIGGER_FALLING|SA_TRIGGER_LOW,"eint10",NULL);
    printk("request_irq ret:%d %d\n",ret,IRQ_EINT10);
    if(ret){
        printk("open failed!\n");
        return -1;
    }

    ret = 0;
    return ret;
}

 
static ssize_t key_drv_read(struct file *file,char __user *userbuf,size_t count,loff_t *off)
{
  int ret = 0;
 
  printk("key_drv_read()\n");
  printk("%s:%d\n",__func__,__LINE__);

 // wait_event_interruptible(button_waitq, ev_press);
  //ret = copy_to_user(userbuf,&back_value,1);
 // ev_press = 0;
 // if(ret){
 //     printk("copy  failed! ret:%d\n",ret);
  //    return -1;
  //}
  return ret;
}
static int key_drv_close(struct inode *inode,struct file *file)
{
    free_irq(IRQ_EINT10,NULL);
    return 0;  
}

static struct file_operations key_drv_ops = 
{
    .owner = THIS_MODULE,
    .open  = key_drv_open,
    .read  = key_drv_read,
    .release = key_drv_close,
   
};

static int __init key_chr_init(void)
{ 
  int ret = 0;
  key_chrdrv = kmalloc(sizeof(struct key_drv), GFP_KERNEL);
  if(key_chrdrv == NULL)
  {
      printk("malloc error\n");
      return -1;
  }
  printk("malloc ok!\n");
  key_chrdrv->major = register_chrdev(0,"chr_key",&key_drv_ops); //注册驱动程序
  if(key_chrdrv->major < 0){
      ret = -2;
      printk("register_chrdev failed\n");
      goto ERROR_1;
  }
  printk("key_chrdrv->major:%d\n",key_chrdrv->major);
  key_chrdrv->third_drv_cls = class_create(THIS_MODULE,"chr_key");
  if(IS_ERR(key_chrdrv->third_drv_cls)){
      printk("register class failed \n");
      ret = -3;
      goto ERROR_2;
  } 
  printk("register class ok \n");
  key_chrdrv->third_drv_dev = device_create(key_chrdrv->third_drv_cls,NULL,MKDEV(key_chrdrv->major,0),NULL,"button_irq");
  if(IS_ERR(key_chrdrv->third_drv_dev)){
      printk("register dev failed\n");
      ret = -4;
      goto ERROR_3;
  }
  
  printk("device_create ok\n");
  key_chrdrv->gpfcon = ioremap(BACK_HOME_CONFIG_BASE,2);
  key_chrdrv->gpfdat = key_chrdrv->gpfcon +1;
  *key_chrdrv->gpfcon &= ~(0xFFFFFFFF);
  *key_chrdrv->gpfcon |= ~(0xFFFFF0FF);


  if(IS_ERR(key_chrdrv->gpfcon))
  {
      ret = -5;
      goto ERROR_4;
  }
    printk("chrdev register ok!\n");
  return ret;
ERROR_4:
    device_destroy(key_chrdrv->third_drv_cls,MKDEV(key_chrdrv->major,0));
ERROR_3:
    class_destroy(key_chrdrv->third_drv_cls);
ERROR_2:
    unregister_chrdev(key_chrdrv->major,"chr_key"); 
ERROR_1:
    kfree(key_chrdrv);

    return ret;    
}
static void __exit key_chr_exit(void)
{
    printk("*****key_chr_exit*******\n");
    iounmap(key_chrdrv->gpfcon);
    printk("iounmap\n");

    device_destroy(key_chrdrv->third_drv_cls,MKDEV(key_chrdrv->major,0));
    printk("device_destroy\n");

    class_destroy(key_chrdrv->third_drv_cls);
    printk("class_destroy\n");

    unregister_chrdev(key_chrdrv->major,"chr_key");
    printk("unregister_chrdev\n");

    kfree(key_chrdrv);
    printk("key_chr_exit end!\n");
}

module_init(key_chr_init);
module_exit(key_chr_exit);
MODULE_LICENSE("GPL");





