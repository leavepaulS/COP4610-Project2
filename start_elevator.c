#include<linux/linkage.h>

#include<linux/kernel.h>

#include<linux/module.h>

#include<linux/syscalls.h>

#include<linux/init.h>




long (*STUB_start_elevator)(void) = NULL;

EXPORT_SYMBOL(STUB_start_elevator);

SYSCALL_DEFINE0(start_elevator) {

        if (STUB_start_elevator)

                return STUB_start_elevator();

        else

                return -ENOSYS;

}

