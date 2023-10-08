#include "monty.h"

/**
 * free_stack - free memory space allocated for the stack
 * @stack: pointer to top of stack
 *
 * Return: nothing
 */
void free_stack(stack_t **stack)
{
	stack_t *free_next;

	if (stack == NULL || *stack == NULL)
		return;
	while ((*stack)->prev != NULL)
	{
		free_next = *stack;
		*stack = (*stack)->prev;
		free(free_next);
	}
	free_next = *stack;
	*stack = NULL;
	free(free_next);
}
