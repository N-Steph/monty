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

/**
 * pint - prints the value at the top of the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void pint(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	if (stack == NULL)
		return;
	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pint, stack empty\n", line_number);
		errno = -1;
		return;
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pop - removes the top element of the stack
 * @stack: stack containing value to pint
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void pop(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *to_free;

	if (stack == NULL)
		return;
	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pop an empty stack", line_number);
		errno = -1;
		return;
	}
	if ((*stack)->prev == NULL)
	{
		free(*stack);
		*stack = NULL;
		return;
	}
	to_free = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(to_free);
}

/**
 * swap - swaps the top two elements of the stack
 * @stack: stack containing value to swap
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void swap(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	int temp;
	size_t len;

	if (stack == NULL)
		return;
	len = dlistint_len(*stack);
	if (len < 2)
	{
		dprintf(STDERR_FILENO, "L%d: can't swap, stack too short", line_number);
		errno = -1;
		return;
	}
	temp = (*stack)->n;
	(*stack)->n = (*stack)->prev->n;
	(*stack)->prev->n = temp;
}
