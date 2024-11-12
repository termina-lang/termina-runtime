#ifndef __TERMINA__PLATFORM__PLATFORM_H__
#define __TERMINA__PLATFORM__PLATFORM_H__

#include <rtems.h>

/**
 * \brief Installs a new interrupt service routine.
 *
 * @param[in] vector        the interrupt vector.
 * @param[in] handler       the interrupt service routine to install.
 * 
 * @return the status code returned by the system call.
 *
 */
rtems_status_code __rtems__install_isr(rtems_vector_number vector,
                                       rtems_isr_entry handler);


#endif // __TERMINA__PLATFORM__PLATFORM_H__
