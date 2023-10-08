#include "monty.h"

/**
 * push - pushes an element to the stack
 * @stack: stack to push element inside
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void push(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *new_node;

	if (stack == NULL)
		return;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		free_stack(stack);
		exit(EXIT_FAILURE);
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
 * pall - prints all the values on the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void pall(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *next;

	if (stack == NULL || *stack == NULL)
		return;
	next = *stack;
	while (next != NULL)
	{
		printf("%d\n", next->n);
		next = next->prev;
	}
}
