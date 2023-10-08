#include "monty.h"

/**
 * dlistint_len - counts the number of elements in a linked dlistint_t list
 * @stack: address of head node
 *
 * Return: the number of elements
 */
size_t dlistint_len(stack_t *stack)
{
	size_t num_node;

	if (stack == NULL)
		return (0);
	num_node = 0;
	while (stack != NULL)
	{
		stack = stack->prev;
		++num_node;
	}
	return (num_node);
}
