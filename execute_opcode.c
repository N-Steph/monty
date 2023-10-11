#include "monty.h"

/**
 * execute_opcode - execute the function pointed by opcode
 * @opcd_read: array containg opcode and/or data to execute
 * @line_num: line at which opcode was read
 * @stack: stack containing integer
 * @ds: sets the data format to use
 *
 * Return: -1 (failure), 0 (success)
 */
int execute_opcode(stack_t **stack, char **opcd_read, size_t line_num, int ds)
{
	char *data, *digit = "0123456789";
	int status, error_code;
	void (*handler)(stack_t **stack, unsigned int line_number);

	if (strcmp(opcd_read[0], "#") == 0 || opcd_read[0][0] == '#')
		return (0);
	status = check_opcode(opcd_read[0], line_num, opcd_read);
	if (status != 0)
		return (-1);
	handler = opcode_handler_selector(opcd_read[0], ds);
	if (strcmp(opcd_read[0], "push") == 0)
	{
		if (opcd_read[1] == NULL)
		{
			error_push(line_num);
			return (-1);
		}
		data = opcd_read[1];
		while (*data != '\0')
		{
			if (strchr(digit, *data) == NULL)
			{
				error_push(line_num);
				return (-1);
			}
			data++;
		}
		integer = atoi(opcd_read[1]);
	}
	error_code = errno;
	handler(stack, line_num);
	if (error_code != errno)
		return (-2);
	return (0);
}

/**
 * check_opcode - checks if the opcode read is a valid one
 * @ptr: points to the opcode read from monty file
 * @ln: line at which opcode was read
 * @opcd_read: array containing opcode and/or data
 *
 * Return: 0 (if opcode is correct), -1 otherwise
 */
int check_opcode(char *ptr, size_t ln, char **opcd_read)
{
	char *opcode_list[] = {"push", "pall", "pint",
		"pop", "swap", "add", "nop", "sub",
		"div", "mul", "mod", "pchar", "pstr",
		"rotl", "rotr", NULL};
	int i;

	i = 0;
	while (opcode_list[i] != NULL)
	{
		if (strcmp(opcode_list[i], opcd_read[0]) == 0)
			return (0);
		i++;
	}
	error_opcode(ptr, ln);
	return (-1);
}

/**
 * error_opcode - handles error in opcode
 *
 * Description: prints error message in case opcode is invalid
 *
 * @ptr: points to opcode
 * @line_number: line at which opcode is
 *
 * Return: nothing
 */
void error_opcode(char *ptr, size_t line_number)
{
	dprintf(STDERR_FILENO, "L%ld: unknown instruction %s\n", line_number, ptr);
}

/**
 * error_push - handles error in push instruction
 *
 * Description: prints error message in case data of push opcode is invalid
 *
 * @line_number: line at which opcode is
 *
 * Return: nothing
 */
void error_push(size_t line_number)
{
	dprintf(STDERR_FILENO, "L%ld: usage: push integer\n", line_number);
}
