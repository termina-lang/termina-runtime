#ifndef __TERMINA__OPTION_H__
#define __TERMINA__OPTION_H__

/* Termina common types */
#include <termina/types.h>

typedef struct {
    // \brief Pointer to the data 
    void * data;
    // \brief Pointer to the pool that originated the data
    __termina_pool_t * pool;
} __termina_dyn_t;


/**
 * \brief Enumeration of the possible variants of the Result type.
 */
typedef enum {
    __Option_Some,
    __Option_None
} __enum_Option_t;

typedef struct {
    __termina_dyn_t __0;
} __enum_Option_Some_params_t;

/**
 * \brief Structure used to implement the dynamic subtyping relationship.
 */
typedef struct {

    // \brief The current variant.
    __enum_Option_t __variant;

    // \brief The parameter of the Somevariant.
    __enum_Option_Some_params_t Some;

} Option;


#endif // __TERMINA__OPTION_H__
