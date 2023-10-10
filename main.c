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
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t char_read = 0;
	unsigned int line_number;
	stack_t *stack = NULL;
	int exec_status;

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
	line_number = 0;
	while ((char_read = getline(&lineptr, &n, monty_file) >= 0))
	{
		line_number++;
		if (strcmp(lineptr, "\n") == 0 || lineptr[0] == '#')
		{
			free(lineptr);
			lineptr = NULL;
			continue;
		}
		exec_status = execute_opcode(&stack, lineptr, line_number);
		clean_up_selector(exec_status, &stack, lineptr, monty_file);
		lineptr = NULL;
	}
	clean_up(&stack, lineptr, monty_file);
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
void clean_up_selector(int status, stack_t **stack, char *ptr, FILE *fptr)
{
	if (status == -1)
	{
		clean_up(stack, ptr, fptr);
		exit(EXIT_FAILURE);
	}
	else if (status == -2)
	{
		clean_up_handler_fail(stack, fptr);
		exit(EXIT_FAILURE);
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
 * clean_up_handler_fail - do some clean up before ending program
 * @stack: stack containing integers
 * @fileptr: file pointer
 *
 * Return: nothing
 */
void clean_up_handler_fail(stack_t **stack, FILE *fileptr)
{
	free_stack(stack);
	fclose(fileptr);
}
