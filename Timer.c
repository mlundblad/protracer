#include <sys/time.h>
#include <stdio.h>
#include "Timer.h"

struct itimerval alex_timer;
struct itimerval alex_timer_saved;

/* ----------------------------------------------------------------------
    Initialize timer
   ---------------------------------------------------------------------- */

void Timer_initialize()
{
    alex_timer.it_value.tv_sec = 1000000;
    alex_timer.it_value.tv_usec = 0;
    alex_timer.it_interval.tv_sec = 0;
    alex_timer.it_interval.tv_usec = 1;

    alex_timer_saved = alex_timer;

    setitimer( ITIMER_VIRTUAL, &alex_timer, NULL );
}

/* ----------------------------------------------------------------------
    Reset timer to 0
   ---------------------------------------------------------------------- */

void Timer_reset()
{
    getitimer( ITIMER_VIRTUAL, &alex_timer );
    alex_timer_saved = alex_timer;
}

/* ----------------------------------------------------------------------
    Return timer value in milliseconds
   ---------------------------------------------------------------------- */

int Timer_getMilliseconds()
{
    getitimer( ITIMER_VIRTUAL, &alex_timer );
    return (alex_timer_saved.it_value.tv_sec -
	    alex_timer.it_value.tv_sec) * 1000 +
           (alex_timer_saved.it_value.tv_usec -
	    alex_timer.it_value.tv_usec) / 1000;
}
