#include "monty.h"

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
		errno = -1;
		return;
	}
	(*stack)->prev->n = (*stack)->n + (*stack)->prev->n;
	temp = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(temp);
}

/**
 * sub - substracts the top element of the stack from the second
 * top element of the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	size_t len;

	if (stack == NULL)
		return;
	len = dlistint_len(*stack);
	if (len < 2)
	{
		dprintf(STDERR_FILENO, "L%d: can't sub, stack too short\n", line_number);
		errno = -1;
		return;
	}
	(*stack)->prev->n = (*stack)->prev->n - (*stack)->n;
	temp = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(temp);
}

/**
 * division - divides the second top element of the stack by the top
 * element of the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void division(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	size_t len;

	if (stack == NULL)
		return;
	len = dlistint_len(*stack);
	if (len < 2)
	{
		dprintf(STDERR_FILENO, "L%d: can't div, stack too short\n", line_number);
		errno = -1;
		return;
	}
	if ((*stack)->n == 0)
	{
		dprintf(STDERR_FILENO, "L%d: division by zero\n", line_number);
		errno = -1;
		return;
	}
	(*stack)->prev->n = (int) ((*stack)->prev->n / (*stack)->n);
	temp = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(temp);

}

/**
 * mul - multiplies the second top element of the stack with the top
 * element of the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	size_t len;

	if (stack == NULL)
		return;
	len = dlistint_len(*stack);
	if (len < 2)
	{
		dprintf(STDERR_FILENO, "L%d: can't mul, stack too short\n", line_number);
		errno = -1;
		return;
	}
	(*stack)->prev->n = (*stack)->prev->n * (*stack)->n;
	temp = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(temp);

}

/**
 * mod - computes the rest of the division of th second top
 * element of the stack by the top element of the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	size_t len;
	int result;

	if (stack == NULL)
		return;
	len = dlistint_len(*stack);
	if (len < 2)
	{
		dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", line_number);
		errno = -1;
		return;
	}
	if ((*stack)->n == 0)
	{
		dprintf(STDERR_FILENO, "L%d: division by zero\n", line_number);
		errno = -1;
		return;
	}
	result = (int)((*stack)->prev->n / (*stack)->n);
	result = (*stack)->prev->n - (*stack)->n;
	(*stack)->prev->n = result;
	temp = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	free(temp);

}
