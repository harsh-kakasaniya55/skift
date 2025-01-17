#include <libsystem/thread/Atomic.h>

#include "arch/Arch.h"
#include "kernel/interrupts/Dispatcher.h"
#include "kernel/interrupts/Interupts.h"

void interrupts_initialize()
{
    dispatcher_initialize();
    atomic_enable();
    arch_enable_interrupts();
}
