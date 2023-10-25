#ifndef __TERMINA__TYPES_H__
#define __TERMINA__TYPES_H__

#include <stdint.h>


/**
 * \brief Enumeration of the possible variants of the TaskRet type.
 */
typedef enum {
    __TaskRet_Continue,
    __TaskRet_Finish,
    __TaskRet_Abort
} __enum_TaskRet_t;

/**
 * \brief Structure that stores the parameter of the Error variant of the
 *        Result enumeration type. This parameter is runtime-dependent and
 *        is used to codify the source of the error.
 */
typedef struct {
    uint32_t __0;
} __enum_TaskRet_Abort_params_t;

/**
 * \brief Structure that implements the TaskRet type.
 */
typedef struct {

    // \brief The current variant.
    __enum_TaskRet_t __variant;

    // \brief The parameters of the Abort variant.
    __enum_TaskRet_Abort_params_t Abort;

} TaskRet;


/**
 * \brief Enumeration of the possible variants of the Result type.
 */
typedef enum {
    __Result_Ok,
    __Result_Error
} __enum_Result_t;

/**
 * \brief Structure that stores the parameter of the Error variant of the
 *        Result enumeration type. This parameter is runtime-dependent and
 *        is used to codify the source of the error.
 */
typedef struct {
    uint32_t __0;
} __enum_Result_Error_params_t;

/**
 * \brief Structure that implements the Result type.
 */
typedef struct {

    // \brief The current variant.
    __enum_Result_t __variant;

    // \brief The parameters of the Error variant.
    __enum_Result_Error_params_t Error;

} Result;


/**
 * \brief Structure that implements the TimeVal type.
 */
typedef struct {
    uint32_t tv_sec;
    uint32_t tv_usec;
} TimeVal;

/**
 * \brief Structure used to implement memory pools.
 */
typedef struct {

    //! Address of the memory area that stores the blocks.
    uint8_t * memory_area;

    //! Size of the memory area in bytes.
    uint32_t memory_area_size;

    //! Size of the data blocks.
    uint32_t data_size;

    //! Number of free blocks.
    uint32_t free_blocks;

    //! Address of the list of free blocks.
    void * free_blocks_list;

} __termina_pool_t;


#endif // __TERMINA__TYPES_H__
