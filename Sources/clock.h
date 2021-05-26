#ifndef CLOCK_H
#define CLOCK_H

#define WATCH_DOG_ENABLE		1
#define WATCH_DOG_DISABLE	0

/**/
void clock_init();
void clock_init_PEE();
void clock_init_PEI();
void watchDog_init();
void watchDog_reset();
void watchDog_feed();
void resetSoft();
/**/

#endif