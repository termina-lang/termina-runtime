#ifndef __TERMINA__RESOURCE_H__
#define __TERMINA__RESOURCE_H__

#include <stdint.h>

#include <termina/types.h>
#include <termina/option.h>
#include <termina/os/types.h>

/**
 * \brief Initializes a resource. This routine is not meant to be called 
 *        from termina code, but from the generated glue code.
 *
 * @param[inout]  resource  the resource.
 *
 * @return Ok if the resource was initialized successfully. Error otherwise.
 */
Result __termina__resource__init(__termina__resource_t * const resource);

/**
 * \brief Locks a resource.
 *
 * @param[inout]  resource the resource.
 *
 */
void __termina__resource__lock(__termina__resource_t * const resource);

/**
 * \brief The resource to unlock.
 *
 * @param[inout]  resource  the resource.
 *
 */
void __termina__resource__unlock(__termina__resource_t * const resource);

#endif // __TERMINA__RESOURCE_H___
