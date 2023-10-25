#include <rtems.h>

#include <termina.h>


Result __termina_message_queue_init(uint32_t count, 
                                    __termina_msg_queue_t * const msg_queue) {

    rtems_status_code status;
    rtems_name r_name;
    rtems_attribute r_attributes;

    Result result;

    result.__variant = __Result_Ok;

    NEXT_RESOURCE_NAME(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
            nmsg_queue_name[3]);
    r_name = rtems_build_name(nmsg_queue_name[0], nmsg_queue_name[1], nmsg_queue_name[2],
            nmsg_queue_name[3]);

    r_attributes = RTEMS_FIFO;

    status = rtems_message_queue_create(r_name, count, sizeof(__termina_dyn_t),
                                        r_attributes, msg_queue);

    if (RTEMS_SUCCESSFUL != status) {

        result.__variant = __Result_Error;
        result.Error.__0 = status;

    }

    return result;

}

void __termina_message_queue_send(__termina_msg_queue_t * const msg_queue, 
                                  __termina_dyn_t element,
                                  Result * const result) {

    rtems_status_code status;

    result->__variant = __Result_Ok;

    status = rtems_message_queue_send(*msg_queue, &element, sizeof(__termina_dyn_t));

    if (RTEMS_SUCCESSFUL != status) {

        result->__variant = __Result_Error;
        result->Error.__0 = status;

    }

    return;

}


void __termina_message_queue_receive(__termina_msg_queue_t * const msg_queue,
                                     Option * const opt,
                                     Result * const result) {
    
    size_t size;

    rtems_status_code status;

    result->__variant = __Result_Ok;

    status = rtems_message_queue_receive(*msg_queue, &opt->Some.__0, &size,
                                         RTEMS_WAIT, RTEMS_NO_TIMEOUT);

    if (RTEMS_SUCCESSFUL != status) {

        opt->__variant = __Option_None;
        
        result->__variant = __Result_Error;
        result->Error.__0 = status;

    } 

}

void __termina_message_queue_receive_timed(
                            __termina_msg_queue_t * const msg_queue, 
                            Option * const opt,
                            const TimeVal * const timeout,
                            Result * const result) {

    size_t size;

    rtems_status_code status;

    opt->__variant = __Option_Some;
    result->__variant = __Result_Ok;

    uint32_t ticks = ((timeout->tv_sec * TICKS_PER_SEC) + 
             (timeout->tv_usec / USECS_PER_TICK));

    status = rtems_message_queue_receive(*msg_queue, &opt->Some.__0, &size,
                                         RTEMS_WAIT, ticks);

    if (RTEMS_SUCCESSFUL != status) {

        opt->__variant = __Option_None;
        
        result->__variant = __Result_Error;
        result->Error.__0 = status;

    }

}
