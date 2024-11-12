#ifndef __TERMINA__OS__OS_H__
#define __TERMINA__OS__OS_H__

#include <rtems.h>

#include <termina/types.h>
#include <termina/os/types.h>

/**
 * \brief Creates a new message queue.
 *
 * @param[in] count             the maximum message and reserved buffer count.
 * @param[in] max_message_size  the maximum size of each message.
 * @param[out] id               the pointer to the queue's identifier.
 * 
 * @return the status code returned by the system call.
 *
 */
rtems_status_code __rtems__create_msg_queue(uint32_t count, 
                                            size_t max_message_size,
                                            rtems_id * id);


/**
 * \brief Creates and starts a new task.
 *
 * @param[in] initial_priority  the initial priority of the new task.
 * @param[in] stack_size        the stack size of the new task.
 * @param[in] entry point       the entry point of the new task.
 * @param[in] argument          the argument to pass to the new task.
 * @param[out] id               the pointer to the task's identifier.
 * 
 * @return the status code returned by the system call.
 *
 */
rtems_status_code __rtems__create_task(rtems_task_priority initial_priority,
                                       size_t stack_size, 
                                       rtems_task_entry entry_point,
                                       rtems_task_argument argument, 
                                       rtems_id * id);


/**
 * \brief Creates a new timer.
 *
 * @param[out] id    the timer's identifier.
 * 
 * @return the status code returned by the system call.
 *
 */
rtems_status_code __rtems__create_timer(rtems_id * id);


/**
 * \brief Programs a timer to wake up at a fixed point in time.
 *
 * @param[in] timer         the timer.
 * @param[in] next_time     time when the timer should trigger.
 * @param[in] routine       the service routine to be called when the timer expires.
 * 
 * @return the status code returned by the system call.
 *
 */
rtems_status_code __rtems__timer_delay_at(rtems_id id,
                                          const TimeVal * next_time,
                                          rtems_timer_service_routine_entry routine);

#endif // __TERMINA__OS__TYPES_H__
