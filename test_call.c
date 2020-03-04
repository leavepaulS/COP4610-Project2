#include<linux/linkage.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/syscalls.h>
#include<linux/linkage.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/syscalls.h>
#include<linux/init.h>
#include<linux/list.h>

#define Dog 2
#define Cat 1
#define Human 3
#define numFloors 10


struct list_head passengerQueue[numFloors];
	
typedef struct item {
	struct list_head list;
	int num;
	int start_floor;
	int dest_floor;
	int type;
	} Item;


extern int (*STUB_issue_request)(int, int, int,int);
int my_issue_request(int num_pets, int pet_type, int start, int dest)
{
	Item* item;
	item = kmalloc(sizeof(Item), __GFP_RECLAIM);
	item->start_floor = start;
  item->dest_floor = dest;
	item->type = type;
	list_add_tail(&item->list, &passengerQueue[start]);
	return 0;
}
