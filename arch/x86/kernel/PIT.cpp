#include "arch/x86/kernel/PIT.h"
#include "arch/x86/kernel/IOPort.h"

void pit_initialize(int frequency)
{
    uint16_t divisor = 1193182 / frequency;

    out8(0x43, 0x36);
    out8(0x40, divisor & 0xFF);
    out8(0x40, (divisor >> 8) & 0xFF);
}
