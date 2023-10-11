#include "monty.h"

/**
 * push_stack - pushes an element to the stack
 * @stack: stack to push element inside
 * @line_num: line at which opcode was read
 *
 * Return: nothing
 */
void push_stack(stack_t **stack, unsigned int __attribute__((unused)) line_num)
{
	stack_t *new_node;

	if (stack == NULL)
		return;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		errno = -1;
		return;
	}
	if (*stack == NULL)
	{
		new_node->n = integer;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	else
	{
		new_node->n = integer;
		new_node->prev = (*stack);
		new_node->next = NULL;
		(*stack)->next = new_node;
	}
	*stack = new_node;
}

/**
 * push_queue - pushes an element to the stack
 * @stack: stack to push element inside
 * @line_num: line at which opcode was read
 *
 * Return: nothing
 */
void push_queue(stack_t **stack, unsigned int __attribute__((unused)) line_num)
{
	stack_t *new_node, *prev_last_node;

	if (stack == NULL)
		return;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		errno = -1;
		return;
	}
	if (*stack == NULL)
	{
		new_node->n = integer;
		new_node->prev = NULL;
		new_node->next = NULL;
		*stack = new_node;
	}
	else
	{
		prev_last_node = *stack;
		while (prev_last_node->prev != NULL)
			prev_last_node = prev_last_node->prev;
		new_node->n = integer;
		new_node->prev = NULL;
		prev_last_node->prev = new_node;
		new_node->next = prev_last_node;
	}
}

