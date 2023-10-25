#ifndef __TERMINA__MSG_QUEUE_H__
#define __TERMINA__MSG_QUEUE_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/option.h>
#include <termina/os/types.h>

/**
 * \brief Initializes a message queue. This routine is not meant to be called 
 *        from termina code, but from the generated glue code.
 *
 * @param[in]  count  maximum number of queued messages.
 * @param[out] id     pointer to the identifier that will store the id of the
 *                    message queue.
 *
 * @return Ok if the message queue was created successfully. Error otherwise.
 */

Result __termina_message_queue_init(uint32_t count, 
                                    __termina_msg_queue_t * const msg_queue);

/**
 * \brief Sends a message through the queue.
 *
 * @param[in]   msg_queue  the message queue.
 * @param[in]   element    the element to be sent.
 * @param[out]  result     pointer to the location where the result value will
 *                         be stored.
 *
 */
void __termina_message_queue_send(__termina_msg_queue_t * const msg_queue, 
                                  __termina_dyn_t element,
                                  Result * const result);

/**
 * \brief Receives a message from a queue. The task blocks forever until a
 *        message is received.
 *
 * @param[inout]  msg_queue  the message queue.
 * @param[in]     opt        pointer to the option element
 * @param[out]    result     pointer to the location where the result value will
 *                           be stored.
 *
 */
void __termina_message_queue_receive(__termina_msg_queue_t * const id,
                                     Option * const opt,
                                     Result * const result);

/**
 * \brief Receives a message from a queue with a timeout.
 *
 * @param[inout]  msg_queue  the message queue.
 * @param[in]     opt        pointer to the option element
 * @param[in]     timeout    the maximum waiting time.
 *
 * @param[out]    result     pointer to the location where the result value will
 *                           be stored.
 *
 */
void __termina_message_queue_receive_timed(
                            __termina_msg_queue_t * const msg_queue, 
                            Option * const opt,
                            const TimeVal * const timeout,
                            Result * const result);

#endif // __TERMINA__MSG_QUEUE_H___
