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
#include <stdio.h>
#include <stdbool.h>

//inverse for stack B check.
bool	ps_israngesorted(t_stack *s, size_t ptr, size_t len, bool inverse)
{
	(void)s;
	(void)ptr;
	(void)len;
	(void)inverse;
	return (true);
}

//check if 
bool	ps_algorithm_recursion(t_stack *s, size_t ptr, size_t len, bool inverse)
{
	(void)s;
	(void)ptr;
	(void)len;
	(void)inverse;
	return (false);
}

bool	ps_algorithm(t_stack *s, const char *output[END_AND_COUNT],
							   const size_t *lengths[END_AND_COUNT],
							   int (*functions[END_AND_COUNT])(bool, t_stack *))
{
	(void)s;
	(void)output;
	(void)lengths;
	(void)functions;
	return true;
}

//hard coded solver for stack size 1, 2, 3 and 4
static inline bool	solve_1234(t_stack *s, bool solve4)
{
	if (solve4 == false)
		return ((s->next[s->a] == 2 && !ra(true, s))
				|| (s->a == 2 && !rra(true, s))
				|| (s->a == 1 && !sa(true, s)));
	else
	{
		if (s->a == 0 || (s->next[s->a] == 0 && ra(true, s))
			|| (s->prev[s->a] == 0 && rra(true, s)))
			return (pa(true, s), solve_1234(s, false), pb(true, s));
		else if (s->a == 3 || (s->next[s->a] == 3 && ra(true, s))
			|| (s->prev[s->a] == 3 && rra(true, s)))
			return (pa(true, s), solve_1234(s, false), pb(true, s), ra(true, s));
	}
	return (true);
}

bool	ps_algorithm_init(t_stack *stack)
{
	int	(*functions[END_AND_COUNT])(bool, t_stack *) =
			{[RRA] = rra, [RRB] = rrb, [RRR] = rrr,
			[PA] = pa, [PB] = pb, [RR] = rr, [RB] = rb,
			[RA] = ra, [SA] = sa, [SB] = sb, [SS] = ss};
	const char	*output[END_AND_COUNT] = {[PA] = "pa", [PB] = "pb",
			[SA] = "sa", [SB] = "sb", [SS] = "ss", [RA] = "ra", [RB] = "rb",
			[RR] = "rr", [RRA] = "rra", [RRB] = "rrb", [RRR] = "rrr"};
	const size_t	lengths[END_AND_COUNT] = {[PA] = 2, [PB] = 2,
			[SA] = 2, [SB] = 2, [SS] = 2, [RA] = 2, [RB] = 2,
			[RR] = 2, [RRA] = 3, [RRB] = 3, [RRR] = 3};

	stack->b = SIZE_MAX;
	stack->fd = 1;
	stack->move_count = 0;
	if (stack->size <= 4)
		return (solve_1234(stack, stack->size));
	else
	
	
	
// printf("\n\nindx=[");
// for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", i);
// printf("]\n");
// printf("next=[");
// for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", next[i]);
// printf("]\n");
// printf("prev=[");
// for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", prev[i]);
// printf("]\n");
	// pa(prev, next, stack);
	// sa(prev, next, stack);
	return (true);
}
