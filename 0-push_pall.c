#include "monty.h"

/**
 * main - function that implement push and pall
 * @argc: argument counter
 * @argv: argument vector
 * Return: 0 for success
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	FILE *file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	char *line = NULL;
	size_t line_size = 0;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	while (getline(&line, &line_size, file) != -1)
	{
		line_number++;
		tokenize_and_execute(line, line_number, &stack);
	}

	/* Close the file */
	fclose(file);

	/* Free allocated memory */
	free(line);
	free_stack(stack);

	return (0);
}

