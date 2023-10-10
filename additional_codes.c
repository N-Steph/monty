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
