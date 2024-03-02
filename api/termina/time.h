#ifndef __TERMINA__TIME_H__
#define __TERMINA__TIME_H__

#include <termina/types.h>

typedef struct {

    __termina__timer_t __timer;

    TimeVal period;

} PeriodicTimer;

/**
 * \brief Returns the current uptime.
 *
 * @param[out] uptime   the current uptime.
 *
 */
void __termina__clock_get_uptime(TimeVal * const uptime);

/**
 * \brief Blocks the calling task for a given amount of time.
 *
 * @param[in] time_val  the blocking time.
 *
 */
void __termina__delay_in(const TimeVal * const time_val);


/**
 * \brief Increments one timeval by another.
 *
 * @param[inout] rhs    the timeval to be incremented.
 * @param[in] rhs       the increment.
 *
 */
void __termina__add_timeval(TimeVal * const lhs, const TimeVal * const rhs);


#endif // __TERMINA__TIME_H__
