#include <rtems.h>

#include <termina.h>

Result __termina_resource_init(__termina_resource_t * const resource) {

    Result result;

    result.__variant = __Result_Ok;

    if (__termina_resource_lock_mutex == resource->lock) {

        rtems_status_code status;
        rtems_name r_name;
        rtems_attribute attributes = RTEMS_DEFAULT_ATTRIBUTES;

        NEXT_RESOURCE_NAME(nsem_name[0], nsem_name[1], nsem_name[2], nsem_name[3]);

        r_name = rtems_build_name(nsem_name[0], nsem_name[1], nsem_name[2],
                nsem_name[3]);

        // check priority protocol
        if (__termina_mutex_policy_inherit == resource->mutex.policy) {

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
            
            result.__variant = __Result_Error;

        }

    }

    return result;

}

void __termina_resource_lock(__termina_resource_t * const resource) {

    rtems_status_code status;

    if (__termina_resource_lock_mutex == resource->lock) {
        
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

void __termina_resource_unlock(__termina_resource_t * const resource) {

    rtems_status_code status;


    if (__termina_resource_lock_mutex == resource->lock) {
        
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
