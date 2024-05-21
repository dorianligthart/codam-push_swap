/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:47:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/16 18:15:09 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdint.h>

void	ps_printstack(size_t *next, t_ps_stack *stack, size_t ptr)
{
	ft_printf("%c[HEAD, ", (ptr == stack->a) * 'A' + (ptr == stack->b) * 'B');
	if (ptr != SIZE_MAX)
	{
		ft_printf("%u, ", (unsigned int)ptr);
		ptr = next[ptr];
		while (ptr != stack->a && ptr != stack->b)
		{
			ft_printf("%u, ", (unsigned int)ptr);
			ptr = next[ptr];
		}
	}
	ft_printf("TAIL]\n");
}

// returns the amount of moves needed to solve.
bool	ps_range(size_t range_min, size_t range_max, size_t ptr)
{
	(void)range_min;
	(void)range_max;
	(void)ptr;
	// if ()
	return (true);
}

//NOTE: end range on highest so we only care about lowest.

//	pushes 
bool	ps_push_two_thirds_to_b(size_t *prev, size_t *next,\
								t_ps_stack *stack, bool print)
{
	size_t	range_width;
	size_t	range_mod;
	size_t	i;

	if (print == true)
		stack->print = true;
	range_width = stack->size / 3;
	range_mod = stack->size % 3;
	i = 0;
	while (i < stack->size && stack->a != SIZE_MAX)
	{
		if (stack->a < range_mod)
			ps_pa(prev, next, stack);
		else if (stack->a < range_mod + range_width)
			(ps_pa(prev, next, stack), ps_rrb(prev, next, stack));
		else if (stack->a < stack->size && stack->a >= range_mod + range_width)
			ps_ra(prev, next, stack);
		else
			return (false);
	}
	return (SIZE_MAX);
}

//some value setting function;
//	- b initialised as SIZE_MAX meaning it's empty;
bool	ps_algorithm(size_t *prev, size_t *next,\
					 t_ps_stack *stack, unsigned char *func_seq)
{
	bool	(*function[PS_FUNCTIONS])(size_t *, size_t *, t_ps_stack *) =\
			{[PS_RRA] = ps_rra, [PS_RRB] = ps_rrb, [PS_RRR] = ps_rrr,\
			[PS_PA] = ps_pa, [PS_PB] = ps_pb, [PS_SA] = ps_sa, [PS_SB] = ps_sb,\
		 	[PS_SS] = ps_ss, [PS_RA] = ps_ra, [PS_RB] = ps_rb, [PS_RR] = ps_rr};

	(void)func_seq;
	(void)function;
	(void)prev;
	(void)next;
	(void)stack;
	// stack->a = stack->size - 1;
	// ps_ra(prev, next, stack);
	// ps_ra(prev, next, stack);
	// ps_pa(prev, next, stack);
	ps_pa(prev, next, stack);
	// ps_sa(prev, next, stack);
	ps_printstack(next, stack, stack->a);
	ps_printstack(next, stack, stack->b);
	return (true);
}
