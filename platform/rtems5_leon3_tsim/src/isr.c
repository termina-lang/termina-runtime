
#include <termina.h>

#include <rtems.h>
#include <bsp/irq.h>

rtems_status_code __rtems__install_isr(rtems_vector_number vector,
                                       rtems_isr_entry handler) {

    rtems_status_code status;
    rtems_isr_entry old_handler;

    // Setup interrupt handler
    status = rtems_interrupt_catch(handler, vector, &old_handler);

    return status;

}

