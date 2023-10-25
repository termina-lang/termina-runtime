#ifndef __TERMINA__POOL_H__
#define __TERMINA__POOL_H__

#include <stdint.h>

#include <termina/types.h>

#define TERMINA_POOL_MINIMUM_ELEMENT_SIZE sizeof(void *)

/**
 * \brief Initializes a memory pool.
 *
 * @param[in] pool          pointer to the pool to initialize.
 * @param[in] p_mem_block   pointer to the memory that will be used to allocate
 *                          the blocks.
 * @param[in] memory_size   size of the memory block.
 * @param[in] element_size  size of the elements of the pool.
 */
void __termina_pool_init(__termina_pool_t * pool, uint8_t * p_mem_block,
                         size_t memory_size, size_t element_size);

/**
 * \brief Allocates an element from a given pool.
 *
 * @param[in] pool  pointer to the pool from which the element will be
 *                  allocated.
 * @param[out] opt  pointer to the option variable that will store the valid
 *                  allocated element.
 *
 */
void __termina_pool_alloc(__termina_pool_t * const pool, Option * const opt);

/**
 * \brief Deallocates an element from a given pool.
 *
 * @param[in] pool     pointer to the pool from which the element will be
 *                     deallocated (freed).
 * @param[in] element  pointer to the element to deallocate.
 *
 * @return  Ok if the deallocation was successful. Error if the element did not
 *          belong to the pool.
 */
Result __termina_pool_dealloc(__termina_pool_t * pool, void * element);

#endif // __TERMINA__POOL_H__
