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

// returns the amount of moves needed to solve.
void	getrange(size_t *prev, size_t *next,
					t_stack *stack, t_range *range)
{
	(void)range;
	(void)prev;
	(void)next;
	(void)stack;
}

//	pushes 
bool	rangesort_a_to_b(size_t *prev, size_t *next, t_stack *stack,
							t_range *range)
{
	size_t	range_width;
	size_t	range_mod;
	size_t	i;

	range->size = range->max - range->min;
	range_width = range->size / 3;
	range_mod = range->size % 3;
	i = 0;
	while (i < range->size && stack->a != SIZE_MAX)
	{
		if (stack->a < range_mod)
			pa(prev, next, stack);
		else if (stack->a < range_mod + range_width)
			(pa(prev, next, stack), rrb(prev, next, stack));
		else if (stack->a < range->size && stack->a >= range_mod + range_width)
			ra(prev, next, stack);
		else
			return (false);
	}
	return (SIZE_MAX);
}

	// bool	(*function[FUNCTIONS])(size_t *, size_t *, t_stack *) =
	// 		{[RRA] = (bool (*)(size_t *, size_t *, t_stack *))rra,
	// 		[RRB] = (bool (*)(size_t *, size_t *, t_stack *))rrb,
	// 		[RRR] = (bool (*)(size_t *, size_t *, t_stack *))rrr,
	// 		[PA] = (bool (*)(size_t *, size_t *, t_stack *))pa,
	// 		[PB] = (bool (*)(size_t *, size_t *, t_stack *))pb,
	// 		[SA] = (bool (*)(size_t *, size_t *, t_stack *))sa,
	// 		[SB] = (bool (*)(size_t *, size_t *, t_stack *))sb,
	// 	 	[SS] = (bool (*)(size_t *, size_t *, t_stack *))ss,
	// 		[RA] = (bool (*)(size_t *, size_t *, t_stack *))ra,
	// 		[RB] = (bool (*)(size_t *, size_t *, t_stack *))rb,
	// 		[RR] = (bool (*)(size_t *, size_t *, t_stack *))rr};
bool	algorithm(size_t *prev, size_t *next, t_stack *stack)
{
	bool	(*function[FUNCTIONS])(size_t *, size_t *, t_stack *) =
			{[RRA] = rra, [RRB] = rrb, [RRR] = rrr,
			[PA] = pa, [PB] = pb, [SA] = sa, [SB] = sb,
		 	[SS] = ss, [RA] = ra, [RB] = rb, [RR] = rr};

	stack->print = true;
	// stack->a = stack->size - 1;
	// ra(prev, next, stack);
	// ra(prev, next, stack);
	// pa(prev, next, stack);
	printf("\n\nindx=[");
	for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", i);
	printf("]\n");
	printf("next=[");
	for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", next[i]);
	printf("]\n");
	printf("prev=[");
	for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", prev[i]);
	printf("]\n");
	// sa(prev, next, stack);
	pa(prev, next, stack);
	pa(prev, next, stack);
	pa(prev, next, stack);
	// pa(prev, next, stack);
	// pa(prev, next, stack);
	// pa(prev, next, stack);
	// pa(prev, next, stack);
	// sa(prev, next, stack);
	printf("indx=[");
	for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", i);
	printf("]\n");
	printf("next=[");
	for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", next[i]);
	printf("]\n");
	printf("prev=[");
	for (size_t i = 0; i < stack->size; ++i) printf("%zu, ", prev[i]);
	printf("]\n");
	printstack(next, stack, stack->a);
	printstack(next, stack, stack->b);
	(void)function;
	(void)prev;
	(void)next;
	return (true);
}
