#include "monty.h"

/**
 * nop - doesn't do anything
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void nop(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	if (stack == NULL)
		return;
	if (line_number != 0)
		return;
}

/**
 * add - adds the top two elements of the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void add(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *temp;
	size_t len;

	if (stack == NULL)
		return;
	len = dlistint_len(*stack);
	if (len < 2)
	{
		dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", line_number);
		return;
	}
	(*stack)->prev->n = (*stack)->n + (*stack)->prev->n;
	temp = *stack;
	*stack = (*stack)->prev;
	free(temp);
}
