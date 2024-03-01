#ifndef __TERMINA__OS__TYPES_H__
#define __TERMINA__OS__TYPES_H__

#include <rtems.h>

#include <termina/types.h>

/**
 * \brief Type of message queues.
 */
typedef struct {

    // \brief Identifier of this message queue
    rtems_id msgq_id;

    // \brief Identifier of the single message queue of the receiver
    rtems_id task_msgq_id;

    // \brief Identifier of the port to which the message queue is connected
    uint32_t task_port;

    // \brief Size of the messages
    size_t message_size;

} __termina__msg_queue_t;

/**
 * \brief Type of the task sink ports.
 */
typedef rtems_id __termina__sink_port_t;

/**
 * \brief Type of the task input ports.
 */
typedef rtems_id __termina__in_port_t;

/**
 * \brief Type of the output ports.
 */
typedef __termina__msg_queue_t * __termina__out_port_t;

/**
 * \brief Enumeration of the different types of mutex prioirty policies.
 */
typedef enum {

    __RTEMSMutexPolicy__Inherit,
    __RTEMSMutexPolicy__Ceiling

} __rtems__runtime_mutex_policy;

/**
 * \brief Enumeration of the different types of locking mechanisms.
 */
typedef enum {

    __RTEMSResourceLock__None,
    __RTEMSResourceLock__Mutex,
    __RTEMSResourceLock__Irq

} __rtems__runtime_resource_lock_t;

typedef struct {

    // Id of the mutex 
    rtems_id mutex_id;
    __rtems__runtime_mutex_policy policy;
    rtems_task_priority prio_ceiling;

} __rtems__runtime_resource_lock_mutex_params_t;

typedef struct {

    // Previous interrupt level
    rtems_interrupt_level old_level;

} __rtems__runtime_resource_lock_irq_params_t;

typedef struct {

    // Type of locking mechanism
    __rtems__runtime_resource_lock_t lock;

    union {
        __rtems__runtime_resource_lock_mutex_params_t mutex;
        __rtems__runtime_resource_lock_irq_params_t irq;
    };

} __termina__resource_t;

#endif // __TERMINA__OS__TYPES_H__
