#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");

static int timer_init(void)
{
 printk(KERN_INFO "current time: %ld\n",current_kernel_time().tv_sec);
 return 0;
}

static void timer_exit(void)
{
 return;
}


module_init(timer_init);
module_exit(timer_exit);



