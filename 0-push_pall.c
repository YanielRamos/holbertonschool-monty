#include "monty.h"

/* Global variable */
stack_t *stack = NULL;

/* Function prototypes */
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void free_stack(stack_t *stack);

/* Instruction function array */
instruction_t instructions[] = {
    {"push", push},
    {"pall", pall},
    {NULL, NULL}
};

/* Push function */
void push(stack_t **stack, unsigned int line_number)
{
    /* Get the integer argument */
    char *arg = strtok(NULL, " \n");
    if (arg == NULL)
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    /* Convert the argument to an integer */
    int value;
    if (sscanf(arg, "%d", &value) != 1)
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    /* Create a new stack node */
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

/* Pall function */
void pall(stack_t **stack, unsigned int line_number)
{
    (void)line_number;  /* Unused parameter */

    /* Print the values on the stack */
    stack_t *current = *stack;
    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}

/* Free the stack */
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

/* Main function */
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

    while (getline(&line, &line_size, file) != -1)
    {
        line_number++;

        /* Get the opcode */
        char *opcode = strtok(line, " \n");
        if (opcode == NULL || opcode[0] == '#')
            continue;  /* Empty line or comment, skip to next iteration */

        /* Find the corresponding instruction function */
        int i = 0;
        while (instructions[i].opcode != NULL)
        {
            if (strcmp(opcode, instructions[i].opcode) == 0)
            {
                instructions[i].f(&stack, line_number);
                break;
            }
            i++;
        }

        /* Check if the opcode is unknown */
        if (instructions[i].opcode == NULL)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
    }

    /* Close the file */
    fclose(file);

    /* Free allocated memory */
    free(line);
    free_stack(stack);

    return 0;
}

