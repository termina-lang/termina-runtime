#ifndef __TERMINA__OS__TYPES_H__
#define __TERMINA__OS__TYPES_H__

#include <rtems.h>

#include <termina/types.h>

/**
 * \brief Type of tasks, task functions and arguments.
 */
typedef struct { 

    //! The identifier of the task.
    rtems_id task_id;

    //! The entry point of the task.
    rtems_task_entry entry;

    //! The initial argument of the task.
    rtems_task_argument argument;

    //! The priority of the task.
    rtems_task_priority priority;

    //! The minimum stack size of the task.
    size_t stack_size;

} __termina_task_t;

/**
 * \brief Type of interrupt handler functions and vector numbers.
 */
typedef struct {

    rtems_isr_entry func;
    void * argument;

} __termina_handler_t;

typedef rtems_vector_number __termina_irq_vector_t;

/**
 * \brief Type of message queues.
 */
typedef struct {

    rtems_id msg_queue_id;
    uint32_t count;

} __termina_msg_queue_t;

/**
 * \brief Enumeration of the different types of mutex prioirty policies.
 */
typedef enum {

    __termina_mutex_policy_inherit,
    __termina_mutex_policy_ceiling,

} __termina_mutex_policy;

/**
 * \brief Enumeration of the different types of locking mechanisms.
 */
typedef enum {

    __termina_resource_lock_mutex,
    __termina_resource_lock_irq

} __termina_resource_lock_t;

typedef struct {

    // Id of the mutex 
    rtems_id mutex_id;
    __termina_mutex_policy policy;
    rtems_task_priority prio_ceiling;

} __termina_resource_lock_mutex_params_t;

typedef struct {

    // Previous interrupt level
    rtems_interrupt_level old_level;

} __termina_resource_lock_irq_params_t;

typedef struct {

    // Type of locking mechanism
    __termina_resource_lock_t lock;

    union {
        __termina_resource_lock_mutex_params_t mutex;
        __termina_resource_lock_irq_params_t irq;
    };

} __termina_resource_t;

#endif // __TERMINA__OS__TYPES_H__
