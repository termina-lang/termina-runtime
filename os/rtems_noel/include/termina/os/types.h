#ifndef __TERMINA__OS__TYPES_H__
#define __TERMINA__OS__TYPES_H__

#include <rtems.h>

/**
 * \brief Structure that implements the TimeVal type.
 */
typedef struct {
    uint32_t tv_sec;
    uint32_t tv_usec;
} TimeVal;


/**
 * \brief Type of message queues.
 */
typedef struct {

    // \brief Identifier of the task
    rtems_id task_id;

    // \brief Identifier of the task's notification message queue
    rtems_id msgq_id;

} __termina_task_t;


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

} __termina_msg_queue_t;

/**
 * \brief Type of the task sink ports.
 */
typedef rtems_id __termina_sink_port_t;

/**
 * \brief Type of the task input ports.
 */
typedef rtems_id __termina_in_port_t;

/**
 * \brief Type of the output ports.
 */
typedef __termina_msg_queue_t * __termina_out_port_t;

/**
 * \brief Enumeration of the different types of mutex prioirty policies.
 */
typedef enum {

    __RTEMSMutexPolicy__Inherit,
    __RTEMSMutexPolicy__Ceiling

} __rtems_runtime_mutex_policy;

/**
 * \brief Enumeration of the different types of locking mechanisms.
 */
typedef enum {

    __RTEMSResourceLock__None,
    __RTEMSResourceLock__Mutex,
    __RTEMSResourceLock__Irq

} __rtems_runtime_resource_lock_t;

typedef struct {

    // Id of the mutex 
    rtems_id mutex_id;
    __rtems_runtime_mutex_policy policy;
    rtems_task_priority prio_ceiling;

} __rtems_runtime_resource_lock_mutex_params_t;

typedef struct {

    // Previous interrupt level
    rtems_interrupt_level old_level;

} __rtems_runtime_resource_lock_irq_params_t;

typedef struct {

    // Type of locking mechanism
    __rtems_runtime_resource_lock_t lock;

    union {
        __rtems_runtime_resource_lock_mutex_params_t mutex;
        __rtems_runtime_resource_lock_irq_params_t irq;
    };

} __termina_resource_t;


typedef struct {

    // \brief Identifier of the timer
    rtems_id timer_id;

    // \brief Identifier of the single message queue of the receiver
    rtems_id task_msgq_id;

    // \brief Identifier of the message queue of the sink port of the receiver
    rtems_id sink_msgq_id;

    // \brief Identifier of the port to which the message queue is connected
    uint32_t task_port;

    // \brief the last programmed timer
    TimeVal current;

} __termina_timer_t;

#endif // __TERMINA__OS__TYPES_H__
