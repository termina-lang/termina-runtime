
#include <termina.h>

#include <rtems.h>
#include <bsp/irq.h>

/**
 * \brief Array used to generate the names of the tasks that are created.
 */
int8_t ntask_name[5] = "0000";

/**
 * \brief Array used to generate the names of the semaphore/mutex that are
 *        created.
 */
int8_t nsem_name[5]  = "0000";

/**
 * \brief Array used to generate the names of the message queues that are
 *        created.
 */
int8_t nmsg_queue_name[5]  = "0000";

/**
 * \brief Array used to generate the names of the timers that are created.
 */
int8_t ntimer_name[5]  = "0000";

rtems_status_code __rtems__create_msg_queue(uint32_t count, 
                                            size_t max_message_size, 
                                            rtems_id * id) {

    rtems_status_code status;
    rtems_name name;

    NEXT_OBJECT_NAME(nmsg_queue_name[0], nmsg_queue_name[1],
                     nmsg_queue_name[2], nmsg_queue_name[3]);
    name = rtems_build_name(nmsg_queue_name[0], nmsg_queue_name[1],
                            nmsg_queue_name[2], nmsg_queue_name[3]);

    status = rtems_message_queue_create(name, count, max_message_size,
                                        RTEMS_FIFO, id);

    return status;

}

rtems_status_code __rtems__create_task(rtems_task_priority initial_priority,
                                       size_t stack_size, 
                                       rtems_task_entry entry_point,
                                       rtems_task_argument argument, 
                                       rtems_id * id) {

    rtems_status_code status;
    rtems_name name;
    rtems_mode mode;
    rtems_attribute attributes;

    NEXT_OBJECT_NAME(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);
    name = rtems_build_name(ntask_name[0], ntask_name[1], ntask_name[2],
                            ntask_name[3]);

    mode = RTEMS_PREEMPT | RTEMS_NO_ASR | RTEMS_NO_TIMESLICE
        | RTEMS_INTERRUPT_LEVEL(0);

    attributes = RTEMS_LOCAL;
    
    // Create the task
    status = rtems_task_create(name, initial_priority,
                               stack_size, mode, attributes, id);

    if (RTEMS_SUCCESSFUL == status) {

        status = rtems_task_start(*id, entry_point, argument);

    }

    return status;

}

rtems_status_code __rtems__create_timer(rtems_id * id) {

    rtems_status_code status;
    rtems_name name;

    NEXT_OBJECT_NAME(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);
    name = rtems_build_name(ntimer_name[0], ntimer_name[1], ntimer_name[2],
                            ntimer_name[3]);

    status = rtems_timer_create(name, id);

    return status;

}

rtems_status_code __rtems__install_isr(rtems_vector_number vector,
                                       rtems_interrupt_handler handler) {

    rtems_status_code status;

    // Setup interrupt handler
    status = rtems_interrupt_handler_install(
            RISCV_INTERRUPT_VECTOR_EXTERNAL(vector),
            NULL, RTEMS_INTERRUPT_UNIQUE,
            handler, NULL);

    return status;

}

rtems_status_code __rtems__timer_delay_at(rtems_id id,
                                          const TimeVal * next_time,
                                          rtems_timer_service_routine_entry routine) {

    rtems_status_code status = RTEMS_SUCCESSFUL;

    rtems_interval sleep_time = 0;

    TimeVal current_time;

    current_time.tv_sec = 0;
    current_time.tv_usec = 0;

    __termina__clock_get_uptime(&current_time);

    if (next_time->tv_sec > current_time.tv_sec) {

        TimeVal interval;

        interval.tv_sec = 0;
        interval.tv_usec = 0;

        if (next_time->tv_usec >= current_time.tv_usec) {

            interval.tv_sec = next_time->tv_sec - current_time.tv_sec;
            interval.tv_usec = next_time->tv_usec - current_time.tv_usec;

        } else {

            interval.tv_sec = (uint32_t)(next_time->tv_sec - current_time.tv_sec) - 1;
            interval.tv_usec = 1000000 - 
                (uint32_t)(current_time.tv_usec - next_time->tv_usec);

        }

        sleep_time = (rtems_interval)(interval.tv_sec * TICKS_PER_SEC) + 
                     (rtems_interval)(interval.tv_usec / USECS_PER_TICK);

    } else if (next_time->tv_sec == current_time.tv_sec) {

        if (next_time->tv_usec > current_time.tv_usec) {
    
            TimeVal interval;

            interval.tv_sec = 0;
            interval.tv_usec = next_time->tv_usec - current_time.tv_usec;

            sleep_time = (rtems_interval)(interval.tv_usec / USECS_PER_TICK);

        }

    } else {

        // Do nothing

    }

    if (sleep_time > 0) {

        status = rtems_timer_fire_after(id, sleep_time, routine, NULL);
    }

    return status;

}
