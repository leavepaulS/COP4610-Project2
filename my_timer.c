#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/time.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");

#define BUF_LEN 100

static struct proc_dir_entry* proc_entry;
static long time;

static char msg[BUF_LEN];
static int procfs_buf_len;
static char *message1;

static ssize_t procfile_read(struct file* file, char * ubuf, size_t count, loff_t *ppos)
{
	printk(KERN_INFO "current time: %ld\n", current_kernel_time());
        //printf(msg,"current time: %ld\n", current_kernel_time());
	message1 = kmalloc(sizeof(char) * 256,__GFP_RECLAIM | __GFP_IO | __GFP_FS);
	time = current_kernel_time().tv_sec;
	
	sprintf(message1,"the current time: %ld\n", time);
	procfs_buf_len = strlen(message1);
        
	if (*ppos > 0 || count < procfs_buf_len)
		return 0;

	if (copy_to_user(ubuf,message1, procfs_buf_len))
		return -EFAULT;

	*ppos = procfs_buf_len;

	printk(KERN_INFO "gave to user %s\n", message1);

	return procfs_buf_len;
}


static ssize_t procfile_write(struct file* file, const char * ubuf, size_t count, loff_t* ppos)
{
	printk(KERN_INFO "proc_write\n");

	if (count > BUF_LEN)
		procfs_buf_len = BUF_LEN;
	else
		procfs_buf_len = count;

	copy_from_user(msg, ubuf, procfs_buf_len);

	printk(KERN_INFO "got from user: %s\n", msg);

	return procfs_buf_len;
}


static struct file_operations procfile_fops = {
	.owner = THIS_MODULE,
	.read = procfile_read,
	.write = procfile_write,
};

static int hello_init(void)
{
	proc_entry = proc_create("timed", 0666, NULL, &procfile_fops);

	if (proc_entry == NULL)
		return -ENOMEM;
	
	return 0;
}

static void hello_exit(void)
{
	proc_remove(proc_entry);
	return;
}



module_init(hello_init);
module_exit(hello_exit);

