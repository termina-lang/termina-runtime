#include <rtems.h>

#include <termina.h>


Result __termina__msg_queue_init(__termina_msg_queue_t * const msg_queue,
                                 size_t num_msgs) {

    rtems_status_code status;
    rtems_name r_name;
    rtems_attribute r_attributes;

    Result result;

    result.__variant = Result__Ok;

    NEXT_RESOURCE_NAME(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
            nmsg_queue_name[3]);
    r_name = rtems_build_name(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
            nmsg_queue_name[3]);

    r_attributes = RTEMS_FIFO;

    status = rtems_message_queue_create(r_name, num_msgs, 
                                        sizeof(__termina_dyn_t),
                                        r_attributes, &msg_queue->msg_queue_id);

    if (RTEMS_SUCCESSFUL != status) {

        result.__variant = Result__Error;

    }

    return result;

}

void __termina__msg_queue_send(__termina_msg_queue_t * const msg_queue, 
                               __termina_dyn_t element,
                               Result * const result) {

    rtems_status_code status;

    result->__variant = Result__Ok;

    status = rtems_message_queue_send(msg_queue->msg_queue_id, 
                                      &element, sizeof(__termina_dyn_t));

    if (RTEMS_SUCCESSFUL != status) {

        result->__variant = Result__Error;

    }

    return;

}


void __termina__msg_queue_receive(__termina_msg_queue_t * const msg_queue,
                                  Option * const opt) {
    
    size_t size;

    rtems_status_code status;

    status = rtems_message_queue_receive(msg_queue->msg_queue_id, 
                                         &opt->Some.__0, &size,
                                         RTEMS_WAIT, RTEMS_NO_TIMEOUT);

    if (RTEMS_SUCCESSFUL != status) {

        opt->__variant = __Option_None;

    } 

}

void __termina__msg_queue_receive_timed(__termina_msg_queue_t * const msg_queue, 
                                        Option * const opt,
                                        const TimeVal * const timeout) {

    size_t size;

    rtems_status_code status;

    opt->__variant = __Option_Some;

    rtems_interval ticks = 
        (rtems_interval)(timeout->tv_sec * TICKS_PER_SEC) + 
        (rtems_interval)(timeout->tv_usec / USECS_PER_TICK);

    status = rtems_message_queue_receive(msg_queue->msg_queue_id, 
                                         &opt->Some.__0, &size,
                                         RTEMS_WAIT, ticks);

    if (RTEMS_SUCCESSFUL != status) {

        opt->__variant = __Option_None;

    }

}

void __termina__msg_queue_try_receive(__termina_msg_queue_t * const msg_queue, 
                                      Option * const opt) {

    size_t size;

    rtems_status_code status;

    opt->__variant = __Option_Some;

    status = rtems_message_queue_receive(msg_queue->msg_queue_id, 
                                         &opt->Some.__0, &size,
                                         RTEMS_NO_WAIT, 0);

    if (RTEMS_SUCCESSFUL != status) {

        opt->__variant = __Option_None;

    }

}
