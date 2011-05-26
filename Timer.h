#ifndef _timer_h
#define _timer_h

#include <sys/time.h>
#include <stdio.h>

extern struct itimerval alex_timer;
extern struct itimerval alex_timer_saved;

void Timer_initialize();
void Timer_reset();
int Timer_getMilliseconds();

#endif
