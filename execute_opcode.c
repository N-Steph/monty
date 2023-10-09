#include "monty.h"

/**
 * execute_opcode - execute the function pointed by opcode
 * @ptr: points to opcode to execute
 * @line_number: line at which opcode was read
 * @stack: stack containing integer
 *
 * Return: -1 (failure), 0 (success)
 */
int execute_opcode(stack_t **stack, char *ptr, size_t line_number)
{
	char *opcode_read[3], *data, *digit = "0123456789";
	int status, error_code;
	void (*handler)(stack_t **stack, unsigned int line_number);

	opcode_extractor(ptr, opcode_read);
	status = check_opcode(ptr, line_number, opcode_read);
	if (status != 0)
		return (-1);
	handler = opcode_handler_selector(opcode_read[0]);
	if (strcmp(opcode_read[0], "push") == 0)
	{
		if (opcode_read[1] == NULL)
		{
			error_push(line_number);
			return (-1);
		}
		data = opcode_read[1];
		while (*data != '\0')
		{
			if (strchr(digit, *data) == NULL)
			{
				error_push(line_number);
				return (-1);
			}
			data++;
		}
		integer = atoi(opcode_read[1]);
	}
	status = validate_arg(line_number, opcode_read);
	if (status != 1)
		return (-1);
	free(ptr);
	error_code = errno;
	handler(stack, line_number);
	if (error_code != errno)
		return (-2);
	return (0);
}

/**
 * check_opcode - checks if the opcode read is a valid one
 * @ptr: points to the opcode read from monty file
 * @ln: line at which opcode was read
 * @opcode_read: array containing opcode and/or data
 *
 * Return: 0 (if opcode is correct), -1 otherwise
 */
int check_opcode(char *ptr, size_t ln, char **opcode_read)
{
	char *opcode_list[8] = {"push", "pall", "pint",
		"pop", "swap", "add", "nop", NULL};
	int i;

	if (opcode_read[2] != NULL)
	{
		error_opcode(ptr, ln);
		return (-1);
	}
	i = 0;
	while (opcode_list[i] != NULL)
	{
		if (strcmp(opcode_list[i], opcode_read[0]) == 0)
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

/**
 * validate_arg - handles argument given to opcode
 *
 * Description: prints error message in case opcode is given argument
 * meanwhile it should not
 *
 * @ln: line at which opcode is
 * @opcode_read: array containing opcode and/or data
 *
 * Return: 1 (if argumen is valide), -1 otherwise
 */
int validate_arg(size_t ln, char **opcode_read)
{
	if (strcmp(opcode_read[0], "push") == 0)
		return (1);
	if (opcode_read[1] == NULL)
		return (1);
	dprintf(STDERR_FILENO, "L%ld: usage: %s\n", ln, opcode_read[0]);
	return (-1);
}
