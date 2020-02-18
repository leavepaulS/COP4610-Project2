//
//
//

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUFSIZE 100

MODULE_LICENSE("Daul BSD/GPL");
MODULE_AUTHOR("Santora-Usher-Xing");

static struct proc_dir_entry *entry;

static char msg[BUFSIZE];
static int procfs_buf_len;
static int last_time = 0;

static ssize_t my_read(struct file* file, char* ubuf, size_t count, loff_t* ppos)
{
    //printk(KERN_INFO "proc_read\n");
    procfs_buf_len = strlen(msg);

    if (*ppos > 0 || count < procfs_buf_len)
        return 0;

    if (copy_to_user(ubuf, msg, procfs_buf_len))
        return -EFAULT;

    *ppos = procfs_buf_len;

    printk(KERN_INFO "current time: %ld\n", current_kernel_time());
    if (last_time != 0)
        printk(KERN_INFO "elapsed time: %ld\n", current_kernel_time() - last_time);
    int last_time = (int)current_kernel_time();

    return procfs_buf_len;
}

static ssize_t my_write(struct file* file, const char* ubuf, size_t count, loff_t* ppos)
{
    //printk(KERN_INFO "proc_write\n");

    if (count > BUFSIZE)
        procfs_buf_len = BUFSIZE;
    else
        procfs_buf_len = count;

    copy_from_user(msg, ubuf, procfs_buf_len);

    //printk(KERN_INFO "%s\n", msg);
    
    return procfs_buf_len;
}

static struct file_operations procfile_fops = {
    .owner = THIS_MODULE,
    .read = procfile_read,
    .write = profile_write,
};

static int timer_init(void) //static int __init timer_init(void)
{
    proc_entry = proc_create("timed", 0666, NULL, &procfile_fops);

    if (proc_entry == NULL)
        return -ENOMEM;

    return 0;
}

static void timer_exit(void) //static int __exit timer_exit(void)
{
    proc_remove(proc_entry);
    //return;
}

module_init(timer_init);
module_exit(timer_eixt);
