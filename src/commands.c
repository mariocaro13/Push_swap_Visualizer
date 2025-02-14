#include "visualizer.h"
#include "movements.h"

void execute_operation(t_vars *vars, const char *operation) {
    if (strcmp(operation, "sa") == 0) {
        ft_sa(&vars->stack_a);
    } else if (strcmp(operation, "sb") == 0) {
        ft_sb(&vars->stack_b);
    } else if (strcmp(operation, "pa") == 0) {
        ft_pa(&vars->stack_a, &vars->stack_b);
    } else if (strcmp(operation, "pb") == 0) {
        ft_pb(&vars->stack_a, &vars->stack_b);
    } else if (strcmp(operation, "ra") == 0) {
        ft_ra(&vars->stack_a);
    } else if (strcmp(operation, "rb") == 0) {
        ft_rb(&vars->stack_b);
    } else if (strcmp(operation, "rra") == 0) {
        ft_rra(&vars->stack_a);
    } else if (strcmp(operation, "rrb") == 0) {
        ft_rrb(&vars->stack_b);
    }
    // Incrementa el contador de movimientos
    vars->move_count++;

    // Actualiza el renderizado después de cada movimiento
    draw_bars(vars);
}
