#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "isr.h"
#include "../libc/time.h"

void main()
{
    isr_install();
    irq_install();

    char bufA[100];
    bufA[0] = '\0';

    strcat(bufA, "Test 2");
    kprint(bufA);
}