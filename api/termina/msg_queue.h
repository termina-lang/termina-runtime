#ifndef __TERMINA__MSG_QUEUE_H__
#define __TERMINA__MSG_QUEUE_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/option.h>
#include <termina/os/types.h>

/**
 * \brief Sends a message through the queue.
 *
 * @param[in]   msg_queue  the message queue.
 * @param[in]   element    pointer to the element to be sent.
 *
 */
void __termina_msg_queue__send(__termina_msg_queue_t * const msg_queue, 
                               void * element);


#endif // __TERMINA__MSG_QUEUE_H___
