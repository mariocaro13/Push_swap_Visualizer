#include "visualizer.h"

t_node	*ft_get_last_node(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

int close_window(t_vars *vars) {
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return 0;
}

// Genera una lista de números aleatorios sin repeticiones
void generate_random_numbers(char **str, int size)
{
	int *arr = (int *)malloc(size * sizeof(int));
	int i, j, num;

	srand(time(NULL));
	for (i = 0; i < size; i++)
	{
		do
		{
			num = rand() % size;
			for (j = 0; j < i; j++)
			{
				if (arr[j] == num)
					break;
			}
		} while (j < i);
		arr[i] = num;

		char num_str[16];
		snprintf(num_str, sizeof(num_str), " %d", num);
		*str = realloc(*str, strlen(*str) + strlen(num_str) + 1);
		strcat(*str, num_str);
	}
	free(arr);
}

void update_stacks(t_vars *vars, FILE *pipe) {
    char line[256];

	draw_bars(vars);
    while (fgets(line, sizeof(line), pipe) != NULL) {
        line[strcspn(line, "\n")] = 0;
        execute_operation(vars, line);
        usleep(10000);
    }
    vars->rendering = 0;
	draw_counter(vars);
}

int main(int argc, char **argv) {
    FILE *pipe;
    t_vars vars;
    int size;
    char *command = malloc(1024);

    if (command == NULL) {
        perror("Failed to allocate memory");
        return -1;
    }
    strcpy(command, "./push_swap");

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of elements>\n", argv[0]);
        free(command);
        return -1;
    }

    size = atoi(argv[1]);
    generate_random_numbers(&command, size);
    printf("Command: %s\n", command);

    pipe = popen(command, "r");
    if (!pipe) {
        perror("Failed to run push_swap");
        free(command);
        return 1;
    }

    vars.mlx = mlx_init();
    if (!vars.mlx) {
        perror("Error: mlx");
        free(command);
        return -1;
    }
    vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Visualizer");
    if (!vars.win) {
        perror("Error: win");
        free(command);
        return -1;
    }

    vars.max_size = size;
    vars.stack_a = NULL;
    vars.stack_b = NULL;
	vars.min = INT_MAX;
	vars.max = INT_MIN;
    vars.move_count = 0;
    vars.rendering = 1;

    // Inicializa stack_a con los números generados
    t_node **stack_tail = &vars.stack_a;
    char *token = strtok(command + strlen("./push_swap "), " ");
    while (token != NULL) {
        t_node *new_node = (t_node *)malloc(sizeof(t_node));
        new_node->value = atoi(token);
        new_node->next = NULL;
        *stack_tail = new_node;
        stack_tail = &new_node->next;
        token = strtok(NULL, " ");
    }
    assign_colors_and_set_min_max(&vars);
    update_stacks(&vars, pipe);

    // Ejecutar el loop principal de la ventana
    mlx_hook(vars.win, 17, 0, close_window, &vars);  // Hook para el botón de la X
    mlx_loop_hook(vars.mlx, draw_bars, &vars);
    mlx_loop(vars.mlx);

	
    // Liberar memoria
    pclose(pipe);
    t_node *current;
    while (vars.stack_a != NULL) {
        current = vars.stack_a;
        vars.stack_a = vars.stack_a->next;
        free(current);
    }
    while (vars.stack_b != NULL) {
        current = vars.stack_b;
        vars.stack_b = vars.stack_b->next;
        free(current);
    }

    free(command);
    return 0;
}
