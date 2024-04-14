
#include <termina.h>


Result __termina_pool__init(__termina_pool_t * const pool,
                            void * p_memory_area, size_t memory_area_size, 
                            size_t block_size) {
    Result result;

    result.__variant = Result__Ok;

    if (NULL == pool) {

        /* 
         * We are assuming that the address of pool will be
         * always within limits (i.e. belongs to the data section).
         * If it were NULL, then we must take action from the runtime
         * and, as default, go nuclear (rtems_shutdown_executive()).
         */

        result.__variant = Result__Error;

    }

    if (result.__variant == Result__Ok) {

        // Init the pool as if we were memseting it with zeores

        for (size_t i = 0; i < sizeof(__termina_pool_t); i = i + 1) {

            *(((uint8_t *) pool) + i) = 0;

        }

        // set the pool attributes.

        pool->memory_area = (uintptr_t)p_memory_area;

        pool->memory_area_size = memory_area_size;
        /*
         * Adjust the size of the element so that it is a multiple of
         * TERMINA_POOL_MINIMUM_BLOCK_SIZE.
         */

        if (block_size > 0) { 

            pool->block_size = block_size + 
                (TERMINA_POOL_MINIMUM_BLOCK_SIZE - 
                    (block_size % TERMINA_POOL_MINIMUM_BLOCK_SIZE));

        } else {

            /* 
             * We are going to assume that block_size can never be zero.
             * If it were zero, then we must take action from the runtime
             * and, as default, go nuclear (rtems_shutdown_executive()).
             */

            result.__variant = Result__Error;

        }

    }

    if (result.__variant == Result__Ok) {

        // Init the list of free blocks to the start of the memory area
        pool->free_blocks_list = pool->memory_area;

        // Obtain the maximum number of free blocks.
        pool->free_blocks = pool->memory_area_size / pool->block_size;

        uintptr_t ptr = pool->free_blocks_list;

        // Iterate for the number of blocks.
        for (size_t i = 0; i < (pool->free_blocks - 1); i = i + 1) {

            // Write pointer to the next block
            *(uintptr_t *)ptr = ptr + pool->block_size;

            // Go the next block
            ptr = ptr + pool->block_size;

        }

        // NULL the "next" pointer of the last block.
        *((uintptr_t *) ptr) = (uintptr_t)NULL;

    }

    return result;

}

void __termina_pool__alloc(__termina_pool_t * const pool,
                           __option_dyn_t * const opt) {

    opt->Some.__0.data = NULL;

    // Check if there are free blocks and the pool is not NULL
    if ((NULL != pool) && (pool->free_blocks > 0)) {

        // Get the pointer to the first free block in the list.
        opt->__variant = Some;

        opt->Some.__0.data = (void *)pool->free_blocks_list;
        opt->Some.__0.pool = pool;

        // Update the head of the free blocks list.
        pool->free_blocks_list = *((uintptr_t *) pool->free_blocks_list);

        // Decrease the number of free blocks.
        pool->free_blocks = pool->free_blocks - 1;

    }

}

void __termina_pool__free(__termina_pool_t * const pool, 
                          __termina_dyn_t element) {

    uintptr_t ptr = (uintptr_t)element.data;

    // Sanity check of the element's address
    // - Within the limits of the memory area
    // - Aligned to TERMINA_MINIMUM_BLOCK_SIZE
    if ((ptr >= pool->memory_area)
        && ((ptr % TERMINA_POOL_MINIMUM_BLOCK_SIZE) == 0)
        && (ptr < (pool->memory_area + pool->memory_area_size))) {

        // Add the block to the free blocks list.

        *((uintptr_t *) ptr) = pool->free_blocks_list;

        // Update the head of the free block list.
        pool->free_blocks_list = ptr;

        // Increase the number of free blocks.
        pool->free_blocks = pool->free_blocks + 1;

    } else {

        /* 
         * We are assuming that the address is always correct.
         * If it were not, then we must take action from the runtime
         * and, most likely, go nuclear (rtems_shutdown_executive()).
         */

    }

}
