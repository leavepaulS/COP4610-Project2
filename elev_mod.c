#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#include <linux/list.h>

MODULE_LICENSE("Dual BSD/GPL");

#define BUF_LEN 512
#define MAX_WEIGTH 15

#define CAT 1
#define DOG 2
#define HUMAN 3

static struct proc_dir_entry* proc_entry;
static int procfs_buf_len;

static char *current_state;

// - Elevator Linked List ------------------- //
struct 
{
    char state[8];
    char animal[5];
    int current_floor;
    int passengers;
    int current_weight;
    struct list_head list;
} elevators;

typedef struct Elevator 
{
    int humans;
    int cats;
    int dogs;
    struct list_head list;
} Elevator;
// ------------------------------------------ //

static int passengers_waiting = 0;
static int serviced = 0;

//Floor Information
static int waiting_on_floor[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static char floor_indicator[10] = {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
static char *passenger_types[10]; // human = | , cat = o , dog = x

static ssize_t procfile_read(struct file* file, char * ubuf, size_t count, loff_t *ppos)
{
    message1 = kmalloc(sizeof(char) * 512,__GFP_RECLAIM | __GFP_IO | __GFP_FS);

    sprintf(current_state, "
    Elevator State: %s\n
    Elevator Animals: %s\n
    Current Floor: %d\n
    Number of Passengers: %d\n
    Current Weight: %d\n
    Number of Passengers Waiting: %d\n
    Number of Passengers Seviced: %d\n
    \n
    [%c] Floor 10: %d %s
    [%c] Floor  9: %d %s
    [%c] Floor  8: %d %s
    [%c] Floor  7: %d %s
    [%c] Floor  6: %d %s
    [%c] Floor  5: %d %s
    [%c] Floor  4: %d %s
    [%c] Floor  3: %d %s
    [%c] Floor  2: %d %s
    [%c] Floor  1: %d %s", 
    elevators.state, elevators.animal, elevators.current_floor, elevators.passengers, elevators.current_weight, 
    passengers_waiting, serviced, 
    floor_indicator[9], waiting_on_floor[9], passenger_types[9], 
    floor_indicator[8], waiting_on_floor[8], passenger_types[8], 
    floor_indicator[7], waiting_on_floor[7], passenger_types[7], 
    floor_indicator[6], waiting_on_floor[6], passenger_types[6], 
    floor_indicator[5], waiting_on_floor[5], passenger_types[5], 
    floor_indicator[4], waiting_on_floor[4], passenger_types[4], 
    floor_indicator[3], waiting_on_floor[3], passenger_types[3], 
    floor_indicator[2], waiting_on_floor[2], passenger_types[2], 
    floor_indicator[1], waiting_on_floor[1], passenger_types[1], 
    floor_indicator[0], waiting_on_floor[0], passenger_types[0]);

	procfs_buf_len = strlen(current_state);
	if (*ppos > 0 || count < procfs_buf_len)
		return 0;
	if (copy_to_user(ubuf, current_state, procfs_buf_len))
		return -EFAULT;

	*ppos = procfs_buf_len;

	return procfs_buf_len;
}
static struct file_operations procfile_fops = 
{
	.owner = THIS_MODULE,
	.read = procfile_read,
};
static int elevator_init(void)
{
	proc_entry = proc_create("timed", 0666, NULL, &procfile_fops);

	if (proc_entry == NULL)
		return -ENOMEM;
	
    elevators.current_floor = 1;
    elevators.current_weight = 0;
    elevators.passengers = 0;
    strcpy(elevators.state, "IDLE");
    strcpy(elevators.animal, "");
    INIT_LIST_HEAD(&elevators);

	return 0;
}
static void timer_exit(void)
{
	proc_remove(proc_entry);
	return;
}
module_init(timer_init);
module_exit(timer_exit);