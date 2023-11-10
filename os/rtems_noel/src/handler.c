#include <rtems.h>
#include <bsp/irq.h>

#include <termina.h>

Result __termina__install_handler(__termina_handler_t * const handler) {

    rtems_status_code status;

    Result result;

    result.__variant = Result__Ok;

    // Setup interrupt handler
    status = rtems_interrupt_handler_install(
            RISCV_INTERRUPT_VECTOR_EXTERNAL(handler->vector),
            NULL, RTEMS_INTERRUPT_UNIQUE,
            handler->entry, NULL);

    if(RTEMS_SUCCESSFUL != status) {

        result.__variant = Result__Error;

    }

    return result;

}
