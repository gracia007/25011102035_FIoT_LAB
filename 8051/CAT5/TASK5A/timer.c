#include <reg51.h>

sbit LED = P1^0;              /* change pin to match your board */

/* Number of 2ms ticks needed for 0.4s = 400ms */
#define TICKS_PER_400MS   200U   /* 200 x 2ms = 400ms */

unsigned int tick_count = 0;

void Timer0_ISR(void) interrupt 1
{
    /* Reload Timer0 immediately for the next 2ms interrupt */
    TH0 = 0xF8;
    TL0 = 0xCD;

    tick_count++;

    if (tick_count >= TICKS_PER_400MS)
    {
        LED = !LED;         /* Toggle LED: ON 0.4s, OFF 0.4s */
        tick_count = 0;
    }
}

void Timer0_Init(void)
{
    TMOD &= 0xF0;            /* Clear Timer0 control bits */
    TMOD |= 0x01;             /* Timer0, Mode 1 (16-bit timer) */

    TH0 = 0xF8;                /* Preload high byte for 2ms */
    TL0 = 0xCD;                /* Preload low byte for 2ms */

    ET0 = 1;                   /* Enable Timer0 interrupt */
    EA  = 1;                   /* Enable global interrupts */
    TR0 = 1;                   /* Start Timer0 */
}

void main(void)
{
    LED = 0;                   /* LED initially OFF */

    Timer0_Init();

    while (1)
    {
        /* Main loop stays free for other non-blocking tasks.
           All LED timing is handled entirely inside the ISR. */
    }
}