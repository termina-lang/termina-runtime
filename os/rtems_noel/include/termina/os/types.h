#ifndef __TERMINA__OS__TYPES_H__
#define __TERMINA__OS__TYPES_H__

#include <rtems.h>

#include <termina/types.h>

/**
 * \brief Type alias of the task identifier.
 */
typedef rtems_id __termina_task_t;

/**
 * \brief Type alias of the message queue identifier.
 */
typedef rtems_id __termina_msg_queue_t;

/**
 * \brief Type alias of the interrupt handler routine.
 */
typedef rtems_isr_entry __termina_handler_t;


#endif // __TERMINA__OS__TYPES_H__
