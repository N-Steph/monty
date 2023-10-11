#include "monty.h"

/**
 * opcode_handler_selector - select the required function for an opcode
 * @opcode: opcode whose handler function is to be retrieve
 * @ds: integer indicating the data format to use
 *
 * Return: function pointer
 */
handler opcode_handler_selector(char *opcode, int ds)
{
	int i = 0;
	instruction_t opcode_function[] = {
		{"pint", pint}, {"pop", pop}, {"swap", swap},
		{"pall", pall}, {"add", add}, {"nop", nop}, {"sub", sub},
		{"div", division}, {"mul", mul}, {"mod", mod},
		{"pchar", pchar}, {"pstr", pstr}, {"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	instruction_t push_variants[] = {
		{"push", push_stack}, {"push", push_queue}
	};

	while (opcode_function[i].opcode != NULL)
	{
		if (strcmp(opcode_function[i].opcode, opcode) == 0)
			return (opcode_function[i].f);
		i++;
	}
	if (ds == -1)
		return (push_variants[1].f);
	else
		return (push_variants[0].f);
}
