#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_LICENSE("Dual BSD/GPL");

//constant variables
#define BUF_LEN 512
#define MAX_WEIGTH 15

//weight for each passenger
#define CAT 1
#define DOG 2
#define HUMAN 3

static struct proc_dir_entry* proc_entry;
static int procfs_buf_len;

//string to store proc file elevator state
static char *current_state;

// - Elevator and Linked List --------------- //
struct 
{
    char state[10];
    char animal[5];
    int current_floor;
    int passengers;
    int current_weight;
    struct list_head list;
} elevators;

typedef struct Elevator 
{
    int start_floor;
    int dest_floor;
    int num_pets;
    int type;
    struct list_head list;
} Elevator;
// ------------------------------------------ //

static int passengers_waiting = 0;
static int serviced = 0;

static ssize_t procfile_read(struct file* file, char * ubuf, size_t count, loff_t *ppos)
{
    //floor number for print
    int i;

    //temporary string
    char indicator[50];

    //Floor Information
    int fl_wait[10] = {2, 2, 3, 3, 1, 0, 2, 3, 0, 3};
    char fl_indic[10] = {'*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char *p_typ[10] = {"|x", "|o", "|xx", "|oo", "|", "", "|x", "|oo", "", "|xx"}; 
        // human = | , cat = o , dog = x

    current_state = kmalloc(sizeof(char) * 512,__GFP_RECLAIM | __GFP_IO | __GFP_FS);

    // - formating proc/elevator print out --------------------- //
    sprintf(indicator, "Elevator State: %s\n", elevators.state);
    strcat(current_state, indicator);
    sprintf(indicator, "Elevator Animals: %s\n", elevators.animal);
    strcat(current_state, indicator);
    sprintf(indicator, "Current Floor: %d\n", elevators.current_floor);
    strcat(current_state, indicator);
    sprintf(indicator, "Number of Passengers: %d\n", elevators.passengers);
    strcat(current_state, indicator);
    sprintf(indicator, "Current Weight: %d\n", elevators.current_weight);
    strcat(current_state, indicator);
    sprintf(indicator, "Number of Passengers Waiting: %d\n", passengers_waiting);
    strcat(current_state, indicator);
    sprintf(indicator, "Number of Passengers Seviced: %d\n\n", serviced);
    strcat(current_state, indicator);

    for(i = 9; i >= 0; --i)
    {
        if (i == 9)
            sprintf(indicator, "[%c] Floor %d: %d %s\n", fl_indic[i], i+1, fl_wait[i], p_typ[i]);
        else
            sprintf(indicator, "[%c] Floor  %d: %d %s\n", fl_indic[i], i+1, fl_wait[i], p_typ[i]);
        strcat(current_state, indicator);
    }
    // --------------------------------------------------------- //

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
	proc_entry = proc_create("elevator", 0666, NULL, &procfile_fops);

	if (proc_entry == NULL)
		return -ENOMEM;
    
    //elevators struct initialize
    strcpy(elevators.state, "OFFLINE");
    strcpy(elevators.animal, "");
    elevators.current_floor = 1;
    elevators.passengers = 0;
    elevators.current_weight = 0;

    //Linked List Initialize
    INIT_LIST_HEAD(&elevators.list);

/*
    STUB_issue_request = &(issue_request);
    STUB_start_elevator = &(start_elevator);
    STUB_stop_elevator = &(stop_elevator);
*/

	return 0;
}
static void elevator_exit(void)
{
	proc_remove(proc_entry);

/*
    STUB_issue_request = NULL;
    STUB_start_elevator = NULL;
    STUB_stop_elevator = NULL;
*/
    
	return;
}
module_init(elevator_init);
module_exit(elevator_exit);