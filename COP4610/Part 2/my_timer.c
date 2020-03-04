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
struct timespec time;
struct timespec time2;
static int second = 0;

static int procfs_buf_len;
static char *message1;

static ssize_t procfile_read(struct file* file, char * ubuf, size_t count, loff_t *ppos)
{
	if (second == 0)
	{
		message1 = kmalloc(sizeof(char) * 256,__GFP_RECLAIM | __GFP_IO | __GFP_FS);
		time = current_kernel_time();
		sprintf(message1,"current time: %ld.%ld\n", time.tv_sec, time.tv_nsec);
	}
	else
	{
		message1 = kmalloc(sizeof(char) * 256,__GFP_RECLAIM | __GFP_IO | __GFP_FS);
		time2 = current_kernel_time();
		
		if (time2.tv_nsec - time.tv_nsec < 0)
		{
		
			sprintf(message1,"current time: %ld.%ld\nelapsed time: %ld.%ld\n", time2.tv_sec, time2.tv_nsec, time2.tv_sec - time.tv_sec - 1 , time2.tv_nsec - time.tv_nsec + 1000000000);
		}
		else
		{
			sprintf(message1, "current time: %ld.%ld\nelapsed time: %ld.%ld\n", time2.tv_sec, time2.tv_nsec, time2.tv_sec - time.tv_sec, time2.tv_nsec - time.tv_nsec);
		}
		time = current_kernel_time();
	}
	++second;
	
	
	procfs_buf_len = strlen(message1);
        
	if (*ppos > 0 || count < procfs_buf_len)
		return 0;

	if (copy_to_user(ubuf, message1, procfs_buf_len))
		return -EFAULT;

	*ppos = procfs_buf_len;

	printk(KERN_INFO "gave to user %s\n", message1);

	return procfs_buf_len;
}
static struct file_operations procfile_fops = {
	.owner = THIS_MODULE,
	.read = procfile_read,
};
static int timer_init(void)
{
	proc_entry = proc_create("timed", 0666, NULL, &procfile_fops);

	if (proc_entry == NULL)
		return -ENOMEM;
	
	return 0;
}
static void timer_exit(void)
{
	proc_remove(proc_entry);
	return;
}
module_init(timer_init);
module_exit(timer_exit);