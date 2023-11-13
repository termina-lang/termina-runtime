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

void __termina__delay_at(const TimeVal * const time_val) {

    TimeVal current_time;

    current_time.tv_sec = 0;
    current_time.tv_usec = 0;

    __termina__clock_get_uptime(&current_time);

    if (time_val->tv_sec > current_time.tv_sec) {

        TimeVal next_time;

        next_time.tv_sec = 0;
        next_time.tv_usec = 0;

        if (time_val->tv_usec >= current_time.tv_usec) {

            next_time.tv_sec = time_val->tv_sec - current_time.tv_sec;
            next_time.tv_usec = time_val->tv_usec - current_time.tv_usec;

        } else {

            next_time.tv_sec = (uint32_t)(time_val->tv_sec - current_time.tv_sec) - 1;
            next_time.tv_usec = 1000000 - 
                (uint32_t)(current_time.tv_usec - time_val->tv_usec);

        }

        __termina__delay_in(&next_time);

    } else if (time_val->tv_sec == current_time.tv_sec) {

        if (time_val->tv_usec > current_time.tv_usec) {
    
            TimeVal next_time;

            next_time.tv_sec = 0;
            next_time.tv_usec = time_val->tv_usec - current_time.tv_usec;

            __termina__delay_in(&next_time);

        }

    } else {

        // Do nothing

    }

}
