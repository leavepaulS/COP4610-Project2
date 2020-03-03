
#include<linux/linkage.h>

#include<linux/kernel.h>

#include<linux/module.h>

#include<linux/syscalls.h>

#include<linux/init.h>


long (*STUB_issue_request)(int,int,int, int) = NULL;

EXPORT_SYMBOL(STUB_issue_request);

SYSCALL_DEFINE4(issue-request,int, num_pets, int, pet_type, int, start, int, de$

        if (STUB_issue_request)

                return STUB_issue_request(passenger_type, start_floor, destinat$

        else

                return -ENOSYS;

}

