#ifndef __TERMINA__TIME_H__
#define __TERMINA__TIME_H__

#include <termina/types.h>

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
 * \brief Blocks the calling task until a given point in time is reached.
 *
 * @param[in] time_val  the waking up time.
 *
 */
void __termina__delay_at(const TimeVal * const time_val);

#endif // __TERMINA__TIME_H__
