#include "monty.h"

/**
 * main - Entry point of monty interpreter
 * @argc: argument count
 * @argv: list of command line argument
 *
 * Return: 0 success, -1 otherwise
 */
int main(int argc, char **argv)
{
	FILE *monty_file = NULL;
	char *opcode_read[3], *lineptr = NULL;
	size_t n = 0, line_number = 0;
	ssize_t char_read = 0, exec_status, prev_ds, ds_format = 1;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	monty_file = fopen(argv[1], "r");
	if (monty_file == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((char_read = getline(&lineptr, &n, monty_file) >= 0))
	{
		line_number++;
		opcode_extractor(lineptr, opcode_read);
		prev_ds = ds_format;
		ds_format = ds_format_selector(opcode_read[0]);
		if (ds_format == 0)
			ds_format = prev_ds;
		else
		{
			partial_clean_up(&lineptr);
			continue;
		}
		exec_status = execute_opcode(&stack, opcode_read, line_number, ds_format);
		clean_up_selector(exec_status, &stack, &lineptr, monty_file);
	}
	clean_up(&stack, lineptr, monty_file);
	return (0);
}

/**
 * ds_format_selector - selects the format of the data
 * @ptr: opcode
 *
 * Return: 1 (stack data format), -1 (queue data format), 0 otherwise
 */
int ds_format_selector(char *ptr)
{
	if (strcmp(ptr, "stack") == 0)
		return (1);
	else if (strcmp(ptr, "queue") == 0)
		return (-1);
	else
		return (0);
}

/**
 * clean_up_selector - selection clean up action
 *
 * Description: This function select the clean up action base
 * on the return value of execute_opcode() function
 *
 * @status: return value of execute_opcode()
 * @stack: stack of integer
 * @ptr: pointer to line read
 * @fptr: pointer to monty bytecode file
 *
 * Return: nothing
 */
void clean_up_selector(int status, stack_t **stack, char **ptr, FILE *fptr)
{
	if (status == -1 || status == -2)
	{
		clean_up(stack, *ptr, fptr);
		exit(EXIT_FAILURE);
	}
	else
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * clean_up - do some clean up before ending program
 * @stack: stack containing integers
 * @ptr: pointer to line read
 * @fileptr: file pointer
 *
 * Return: nothing
 */
void clean_up(stack_t **stack, char *ptr, FILE *fileptr)
{
	free(ptr);
	free_stack(stack);
	fclose(fileptr);
}

/**
 * partial_clean_up - do some clean up before continuing reading
 * monty file
 * @lineptr: buffer of line read in monty file
 *
 * Return: nothing
 */
void partial_clean_up(char **lineptr)
{
	free(*lineptr);
	*lineptr = NULL;
}
