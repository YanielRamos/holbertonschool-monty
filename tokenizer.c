#include "monty.h"

/* intructions function array */
instruction_t instructions[] = {
	{"push", push},
	{"pall", pall},
	{"pint", pint},
	{"pop", pop},
	{"swap", swap},
	{"add", add},
	{"nop", nop},
	{NULL, NULL}
};

/**
 * tokenize_and_execute - function that tokenize the line
 * @line: user input
 * @line_number: amount of char
 * Return: void
 */
void tokenize_and_execute(char *line, unsigned int line_number, stack_t **stack)
{
	/* tokenize the line */
	char *opcode = strtok(line, " \n");
	int i = 0;

	if (opcode == NULL || opcode[0] == '#')
		return;

	/* find the corresponding instructions function */
	while (instructions[i].opcode != NULL)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			break;
		}
		i++;
	}

	/* check if the opcode is unknown */
	if (instructions[i].opcode == NULL)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}
