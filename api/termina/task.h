#ifndef __TERMINA__TASK_H__
#define __TERMINA__TASK_H__

#include <termina/types.h>

/**
 * \brief Creates a task with a given priority and stack size and
 *        puts in in the ready state.
 *
 * @param[inout] task      the task.
 *
 * @return Ok if the task was created successfully. Error code otherwise.
 */
Result __termina_task_create(__termina_task_t * task);

#endif // __TERMINA__TASK_H__
