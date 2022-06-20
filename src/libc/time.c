#include "time.h"

u32 tick = 0;

static void timer_int_callback(registers_t regs)
{
    ++tick;
}

void init_timer(u32 freq) 
{
    // sets callback
    register_interrupt_handler(IRQ0, timer_int_callback);

    u32 divisor = 1193180 / freq;
    u8 low = (u8)(divisor & 0xff);
    u8 high = (u8)((divisor >> 8) * 0xff);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}