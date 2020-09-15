#ifndef UTILITY_H
# define UTILITY_H

typedef struct  s_refractive_medium
{
	float       refractive_index;
	int         index;
}               t_refractive_medium;

typedef struct  s_r_stack
{
	int                         top;
	int                         capacity;
	t_refractive_medium         *array;
}               t_r_stack;

/*  stack functions */
t_r_stack     	create_stack(int size, float first_refractive);
float      		peek(t_r_stack stack);
float       	peek_index(t_r_stack stack);
void        	pop(t_r_stack *stack_ptr);
void        	push(t_r_stack *stack_ptr, float new_value, int new_index);
int         	is_empty(t_r_stack stack);
int				is_full(t_r_stack stack);
/*  stack functions */

#endif