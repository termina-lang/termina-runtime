#include <rtems.h>

#include <termina.h>


void __termina__clock_get_uptime(TimeVal * const uptime) {

    struct timeval uptime_timeval;

    /* This workaround is unnecessary, since for the 32-bit NOEL platform,
     * both types are equivalent. However, we are going to make the conversion
     * explicit to denote that the time of tv_sec and tv_usec in the original
     * struct timeval are long int and not fixed-width integer types. */
    rtems_clock_get_uptime_timeval(&uptime_timeval);

    uptime->tv_sec = (uint32_t)uptime_timeval.tv_sec;
    uptime->tv_usec = (uint32_t)uptime_timeval.tv_usec;

    return;

}

void __termina__delay_in(const TimeVal * const time_val) {

    rtems_interval sleep_time = 
        (rtems_interval)(time_val->tv_sec * TICKS_PER_SEC) + 
        (rtems_interval)(time_val->tv_usec / USECS_PER_TICK);

    rtems_task_wake_after(sleep_time);

    return;

}
