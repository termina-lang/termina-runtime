#ifndef __TERMINA__OS__TYPES_H__
#define __TERMINA__OS__TYPES_H__

#include <rtems.h>

#include <termina/types.h>

/**
 * \brief Type of tasks.
 */
typedef struct { 

    //! The identifier of the task.
    rtems_id task_id;

    //! The entry point of the task.
    rtems_task_entry entry;

    //! The initial argument of the task (self)
    rtems_task_argument argument;

    //! The priority of the task.
    rtems_task_priority priority;

    //! The minimum stack size of the task.
    size_t stack_size;

} __termina_task_t;

/**
 * \brief Type of interrupt handlers.
 */
typedef struct {

    rtems_isr_entry entry;
    rtems_vector_number vector;

} __termina_handler_t;

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

#endif // __TERMINA__OS__TYPES_H__
