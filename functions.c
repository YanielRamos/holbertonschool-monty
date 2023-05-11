#include "monty.h"

/**
 * push - function that push
 * @stack: list
 * @line_number: amount of char
 * Return: void
 */

void push(stack_t **stack, unsigned int line_number)
{
	/* Get the integer argument */
	char *arg = strtok(NULL, " \n");
	int value;

	if (arg == NULL)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* Convert the argument to an integer */
	if (sscanf(arg, "%d", &value) != 1)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	/* create a new stack node */
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;

	/* Add the new node to the stack */
	if (*stack != NULL)
		(*stack)->prev = new_node;
	new_node->next = *stack;
	*stack = new_node;
}

/**
 * pall - function that
 * @stack: list with elements
 * @line_number: amount of char
 * Return: void
 */

void pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number; /*unused parameter*/

	/* Print the values on the stack */
	stack_t *current = *stack;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * free_stack - function that frees
 * @stack: elements to be free
 * Return: void
 */

void free_stack(stack_t *stack)
{
	stack_t *current = stack;

	while (current != NULL)
	{
		stack_t *next = current->next;

		free(current);
		current = next;
	}
}

/**
 * pint - function
 * @stack: elements to pint
 * @line_number: number of char
 * Return: void
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}
