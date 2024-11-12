
#include <termina.h>

#include <rtems.h>
#include <bsp/irq.h>

rtems_status_code __rtems__install_isr(rtems_vector_number vector,
                                       rtems_interrupt_handler handler) {

    rtems_status_code status;

    // Setup interrupt handler
    status = rtems_interrupt_handler_install(
            RISCV_INTERRUPT_VECTOR_EXTERNAL(vector),
            NULL, RTEMS_INTERRUPT_UNIQUE,
            handler, NULL);

    return status;

}

