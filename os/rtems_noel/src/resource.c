#include <rtems.h>

#include <termina.h>

Result __termina__resource_init(__termina__resource_t * const resource) {

    Result result;

    result.__variant = Result__Ok;

    if (__RTEMSResourceLock__Mutex == resource->lock) {

        rtems_status_code status;
        rtems_name r_name;
        rtems_attribute attributes = RTEMS_DEFAULT_ATTRIBUTES;

        NEXT_OBJECT_NAME(nsem_name[0], nsem_name[1], nsem_name[2], nsem_name[3]);

        r_name = rtems_build_name(nsem_name[0], nsem_name[1], nsem_name[2],
                nsem_name[3]);

        // check priority protocol
        if (__RTEMSMutexPolicy__Inherit == resource->mutex.policy) {

            attributes = RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE
                | RTEMS_INHERIT_PRIORITY;

        } else {
            // priority ceiling protocol.
            attributes = RTEMS_PRIORITY | RTEMS_BINARY_SEMAPHORE
                | RTEMS_PRIORITY_CEILING | RTEMS_LOCAL;

        }
        // create the semaphore.
        status = rtems_semaphore_create(r_name, 1, attributes, 
                    resource->mutex.prio_ceiling, &resource->mutex.mutex_id);

        if (RTEMS_SUCCESSFUL != status) {
            
            result.__variant = Result__Error;

        }

    }

    return result;

}

void __termina__resource_lock(__termina__resource_t * const resource) {

    rtems_status_code status;

    if (__RTEMSResourceLock__None == resource->lock) {

        // Nothing to do here.

    } else if (__RTEMSResourceLock__Mutex == resource->lock) {
        
        status = rtems_semaphore_obtain(resource->mutex.mutex_id, 
                    RTEMS_WAIT, RTEMS_NO_TIMEOUT);

        if (RTEMS_SUCCESSFUL != status) {

            /* 
             * We are assuming that the obtain can never go wrong. 
             * If something happened, then we must take action from the runtime
             * and, most likely, go nuclear (rtems_shutdown_executive()).
             */
            
        }

    } else {

        rtems_interrupt_disable(resource->irq.old_level);

    }

}

void __termina__resource_unlock(__termina__resource_t * const resource) {

    rtems_status_code status;

    if (__RTEMSResourceLock__None == resource->lock) {

        // Nothing to do here.

    } else if (__RTEMSResourceLock__Mutex == resource->lock) {
        
        status = rtems_semaphore_release(resource->mutex.mutex_id);

        if (RTEMS_SUCCESSFUL != status) {

            /* 
             * We are assuming that the release can never go wrong. 
             * If something happened, then we must take action from the runtime
             * and, most likely, go nuclear (rtems_shutdown_executive()).
             */
            
        }

    } else {

        rtems_interrupt_enable(resource->irq.old_level);

    }

}
