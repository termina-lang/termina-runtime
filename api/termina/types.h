#ifndef __TERMINA__TYPES_H__
#define __TERMINA__TYPES_H__

#include <stdint.h>
#include <stddef.h>


/**
 * \brief Enumeration of the possible variants of the TaskRet type.
 */
typedef enum {
    __TaskRet_Continue,
    __TaskRet_Finish,
    __TaskRet_Abort
} __enum_TaskRet_t;

/**
 * \brief Structure that implements the TaskRet type.
 */
typedef struct {

    // \brief The current variant.
    __enum_TaskRet_t __variant;

} TaskRet;


/**
 * \brief Enumeration of the possible variants of the Result type.
 */
typedef enum {
    __Result_Ok,
    __Result_Error
} __enum_Result_t;

/**
 * \brief Structure that implements the Result type.
 */
typedef struct {

    // \brief The current variant.
    __enum_Result_t __variant;

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
    uintptr_t memory_area;

    //! Size of the memory area in bytes.
    size_t memory_area_size;

    //! Size of the data blocks.
    size_t block_size;

    //! Number of free blocks.
    size_t free_blocks;

    //! Address of the list of free blocks.
    uintptr_t free_blocks_list;

} __termina_pool_t;


#endif // __TERMINA__TYPES_H__
