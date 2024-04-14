#include <rtems.h>

#include <termina.h>


void __termina_msg_queue__send(__termina_msg_queue_t * const msg_queue, 
                               void * element) {

    rtems_status_code status;

    status = rtems_message_queue_send(msg_queue->msgq_id, 
                                      element, msg_queue->message_size);

    if (RTEMS_SUCCESSFUL == status) {

        // Notify the task that a message has been sent
        status = rtems_message_queue_send(msg_queue->task_msgq_id, 
                                          &msg_queue->task_port, 
                                          sizeof(uint32_t));

    }

    return;

}
