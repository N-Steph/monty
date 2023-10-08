#include "monty.h"

/**
 * opcode_handler_selector - select the required function for an opcode
 * @opcode: opcode whose handler function is to be retrieve
 *
 * Return: function pointer
 */
handler opcode_handler_selector(char *opcode)
{
	int i = 0;
	instruction_t opcode_function[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
	};

	while (opcode_function[i].opcode != NULL)
	{
		if (strcmp(opcode_function[i].opcode, opcode) == 0)
			break;
		i++;
	}
	return (opcode_function[i].f);
}
