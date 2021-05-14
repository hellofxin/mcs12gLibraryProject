#ifndef TIMER_G96_H
#define TIMER_G96_H

extern unsigned char timerFlag_1ms;
extern unsigned char timerFlag_5ms;
extern unsigned char timerFlag_10ms;
extern unsigned char timerFlag_20ms;
extern unsigned char timerFlag_50ms;
extern unsigned char timerFlag_100ms;
extern unsigned char timerFlag_200ms;
extern unsigned char timerFlag_1000ms;

void timer_init();
unsigned long timer_getCounter();

#endif