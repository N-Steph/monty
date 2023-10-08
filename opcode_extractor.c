#include "monty.h"

/**
 * opcode_extractor - extract opcode and/or data from line read
 * @ptr: pointer to current line in monty file
 * @opcode_read: an array containing opcode and data
 *
 * Return: nothing
 */
void opcode_extractor(char *ptr, char **opcode_read)
{
	char *delim, *token;
	int i;

	delim = "	 \n";
	token = strtok(ptr, delim);
	i = 0;
	while (i < 2)
	{
		opcode_read[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	opcode_read[i] = token;
}
