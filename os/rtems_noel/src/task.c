#include <rtems.h>

#include <termina.h>


Result __termina_task_create(__termina_task_t * const task) {

    rtems_status_code status;
    rtems_name r_name;
    rtems_mode r_mode;
    rtems_attribute r_attributes;

    Result result;

    result.__variant = __Result_Ok;

    NEXT_RESOURCE_NAME(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);
    r_name = rtems_build_name(ntask_name[0], ntask_name[1], ntask_name[2],
            ntask_name[3]);

    r_mode = RTEMS_PREEMPT | RTEMS_NO_ASR | RTEMS_NO_TIMESLICE
        | RTEMS_INTERRUPT_LEVEL(0);

    r_attributes = RTEMS_LOCAL;

    // Create the task
    status = rtems_task_create(r_name, task->priority,
                               task->stack_size, r_mode, r_attributes, 
                               &task->task_id);

    if (RTEMS_SUCCESSFUL == status) {

        // Put the task in the ready state.
        status = rtems_task_start(task->task_id, task->entry, task->argument);

        if (RTEMS_SUCCESSFUL != status) {
            
            result.__variant = __Result_Error;

        }

    } else {
        
        result.__variant = __Result_Error;

    }

    return result;

}
