#include "minirt.h"

t_r_stack     create_stack(int size, float first_refractive)
{
	t_r_stack stack;

	stack.capacity = size;
	if (!(stack.array = (t_refractive_medium*)malloc(sizeof(t_refractive_medium) * (size + 1))))
		clean_exit(1, "Failed to initialize refraction stack (malloc)");
	stack.array[0].refractive_index = first_refractive;
	stack.array[0].index = -1;
	stack.top = 0;
	return (stack);
}

float       peek(t_r_stack stack)
{
	return(stack.array[stack.top].refractive_index);
}

float       peek_index(t_r_stack stack)
{
	return(stack.array[stack.top].index);
}

void        pop(t_r_stack *stack_ptr)
{
	if(is_empty(*stack_ptr))
	{
		ft_putstr_fd("stack was popped when empty\n", 1);
		return ;
	}
	stack_ptr->top--;
}

void        push(t_r_stack *stack_ptr, float new_value, int new_index)
{
	t_r_stack stack;

	stack = *stack_ptr;
	if (is_full(stack))
	{
		ft_putstr_fd("stack was pushed when full\n", 1);
		return ;
	}
	stack.array[stack.top + 1].refractive_index = new_value;
	stack.array[stack.top + 1].index = new_index;
	stack.top++;
	*stack_ptr = stack;
}

int         is_empty(t_r_stack stack)
{
	return(stack.top < 0);
}

int			is_full(t_r_stack stack)
{
	return (stack.top == stack.capacity - 1);
}