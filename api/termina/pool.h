#ifndef __TERMINA__POOL_H__
#define __TERMINA__POOL_H__

#include <stdint.h>

#include <termina/types.h>

#define TERMINA_POOL_MINIMUM_BLOCK_SIZE sizeof(uintptr_t)

/**
 * \brief Initializes a memory pool.
 *
 * @param[in] pool              pointer to the pool to initialize.
 * @param[in] p_memory_area     pointer to the memory that will be used to allocate
 *                              the blocks.
 * @param[in] memory_area_size  size of the memory area.
 * @param[in] block_size        size of the blocks of the pool.
 *
 * @return Ok if the pool was initialized successfully. Error otherwise.
 */
Result __termina_pool__init(__termina_pool_t * const pool, void * p_memory_area,
                            size_t memory_area_size, size_t block_size);

/**
 * \brief Allocates an element from a given pool.
 *
 * @param[in] pool  pointer to the pool from which the element will be
 *                  allocated.
 * @param[out] opt  pointer to the option variable that will store the valid
 *                  allocated element.
 *
 */
void __termina_pool__alloc(__termina_pool_t * const pool, __option_box_t * const opt);

/**
 * \brief Deallocates an element from a given pool.
 *
 * @param[in] pool     pointer to the pool from which the element will be
 *                     deallocated (freed).
 * @param[in] element  dynamic element to deallocate.
 *
 * @return  Ok if the deallocation was successful. Error if the element did not
 *          belong to the pool.
 */
void __termina_pool__free(__termina_pool_t * const pool, 
                          __termina_box_t element);


/**
 * \brief Returns the size of the memory area for a given pool.
 *
 * @param[in] size       size of each element in bytes (as retured by the sizeof
 *                       operator.
 * @param[in] dimension  number of elements of the pool.
 *
 * @return  size of the memory area of the pool.
 */
#define __termina_pool__size(size, dimension) \
	((size) + (TERMINA_POOL_MINIMUM_BLOCK_SIZE - \
		((size) % TERMINA_POOL_MINIMUM_BLOCK_SIZE)) * (dimension))


#endif // __TERMINA__POOL_H__
