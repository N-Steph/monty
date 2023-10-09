#ifndef MONTY_H
#define MONTY_H

#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Descriptio: opcode and its function for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

typedef void(*handler)(stack_t **stack, unsigned int line_number);
handler opcode_handler_selector(char *opcode);

int integer;
int execute_opcode(stack_t **stack, char *ptr, size_t line_number);
void opcode_extractor(char *ptr, char **opcode_read);
int check_opcode(char *ptr, size_t ln, char **opcode_read);
void error_opcode(char *ptr, size_t line_number);
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void nop(stack_t **stack, unsigned int line_number);
void error_push(size_t line_number);
void free_stack(stack_t **stack);
int validate_arg(size_t ln, char **opcode_read);
void clean_up_selector(int status, stack_t **stack, char *ptr, FILE *fptr);
void clean_up(stack_t **stack, char *ptr, FILE *fileptr);
void clean_up_handler_fail(stack_t **stack, FILE *fileptr);
size_t dlistint_len(stack_t *stack);

#endif /* MONTY_H */
