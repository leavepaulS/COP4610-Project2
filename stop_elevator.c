
#include<linux/linkage.h>

#include<linux/kernel.h>

#include<linux/module.h>

#include<linux/syscalls.h>

#include<linux/init.h>



long (*STUB_stop_elevator)(void) = NULL;

EXPORT_SYMBOL(STUB_stop_elevator);

SYSCALL_DEFINE0(stop_elevator) {

        if (STUB_stop_elevator)

                return STUB_stop_elevator();

        else

                return -ENOSYS;

}

