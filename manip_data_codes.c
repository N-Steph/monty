#include "monty.h"

/**
 * pchar - prints the char at the top of the stack
 * @stack: stack containing value to print
 * @line_num: line at which opcode was read
 *
 * Return: nothing
 */
void pchar(stack_t **stack, unsigned int line_num)
{
	if (stack == NULL)
		return;
	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pchar, stack empty\n", line_num);
		errno = -1;
		return;
	}
	if ((*stack)->n < 0 || (*stack)->n > 127)
	{
		dprintf(STDERR_FILENO, "L%d: can't pchar, value out of range\n", line_num);
		errno = -1;
		return;
	}
	printf("%c\n", (*stack)->n);
}

/**
 * pstr - prints the string starting at the top of the stack
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void pstr(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *temp;

	if (stack == NULL)
		return;
	if (*stack == NULL)
	{
		printf("\n");
		return;
	}
	temp = *stack;
	while (temp != NULL)
	{
		if (temp->n < 32 || temp->n > 126)
			return;
		if (temp->n == 0)
		{
			printf("\n");
			return;
		}
		printf("%c", temp->n);
		temp = temp->prev;
	}
}

/**
 * rotl - rotates the stack to the top
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void rotl(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *last_node, *top_node;

	if (stack == NULL || *stack == NULL || (*stack)->prev == NULL)
		return;
	top_node = *stack;
	last_node = *stack;
	*stack = (*stack)->prev;
	while (last_node->prev != NULL)
		last_node = last_node->prev;
	last_node->prev = top_node;
	top_node->next = last_node;
	top_node->prev = NULL;
	(*stack)->next = NULL;
}

/**
 * rotr - rotates the stack to the bottom
 * @stack: stack containing value to print
 * @line_number: line at which opcode was read
 *
 * Return: nothing
 */
void rotr(stack_t **stack, unsigned int __attribute__((unused)) line_number)
{
	stack_t *last_node, *top_node;

	if (stack == NULL || *stack == NULL || (*stack)->prev == NULL)
		return;
	top_node = *stack;
	last_node = *stack;
	while (last_node->prev != NULL)
		last_node = last_node->prev;
	last_node->next->prev = NULL;
	top_node->next = last_node;
	last_node->next = NULL;
	last_node->prev = top_node;
	*stack = last_node;

}
