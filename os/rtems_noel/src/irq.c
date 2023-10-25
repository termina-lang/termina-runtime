#include <rtems.h>
#include <bsp/irq.h>

#include <termina.h>

Result __termina_install_handler(__termina_handler_t * const handler, 
                                 __termina_irq_vector_t vector) {

    rtems_status_code status;

    Result result;

    result.__variant = __Result_Ok;

    // Setup interrupt handler
    status = rtems_interrupt_handler_install(
            RISCV_INTERRUPT_VECTOR_EXTERNAL(vector),
            NULL, RTEMS_INTERRUPT_UNIQUE,
            handler->func, handler->argument);

    if(RTEMS_SUCCESSFUL != status) {

        result.__variant = __Result_Error;

    }

    return result;

}
