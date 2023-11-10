#ifndef __TERMINA__HANDLER_H__
#define __TERMINA__HANDLER_H__

#include <termina/types.h>


/**
 * \brief Install an interrupt handler.
 *
 * @param[inout] handler    the handler.
 *
 * @return Ok if the handler was installed successfully. Error otherwise.
 */
Result __termina__install_handler(__termina_handler_t * const handler);

#endif // __TERMINA__HANDLER_H__
