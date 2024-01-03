



#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/io.h>        //含有iomap函数iounmap函数
#include <asm/uaccess.h>//含有copy_from_user函数
#include <linux/device.h>//含有类相关的处理函数
#include <linux/irq.h>    //含有IRQ_HANDLED\IRQ_TYPE_EDGE_RISING
#include <linux/interrupt.h> //含有request_irq、free_irq函数

struct class_device * dev;




struct file_operation fops =
{
    
};

void dec()
{
    request_irq();
    
     

    wake_up_interruptible(&button_waitq);
}


module_init();
module_exit();
MOUDLE_LENSE("GPL");

 