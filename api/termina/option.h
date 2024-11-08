#ifndef __TERMINA__OPTION_H__
#define __TERMINA__OPTION_H__

/* Termina common types */
#include <termina/types.h>

typedef struct {
    // \brief Pointer to the data 
    void * data;
    // \brief Pointer to the pool that originated the data
    __termina_pool_t * pool;
} __termina_box_t;

/**
 * \brief Enumeration of the possible variants of the Result type.
 */
typedef enum {
    Some,
    None
} __enum_option_t;

typedef struct {
    __termina_box_t __0;
} __option_box_params_t;

/**
 * \brief Structure used to implement the dynamic subtyping relationship.
 */
typedef struct {

    // \brief The current variant.
    __enum_option_t __variant;

    // \brief The parameter of the Somevariant.
    __option_box_params_t Some;

} __option_box_t;

#endif // __TERMINA__OPTION_H__
