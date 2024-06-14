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
bool	ps_israngesorted(t_stack *s, size_t ptr, t_range *range, bool inverse)
{
	size_t	stay;
	size_t	n;

	if (ptr == SIZE_MAX)
		return (false);
	n = range->max - range->min + 1;
	stay = ptr;
	while (s->next[ptr] != stay && n--)
	{
		if (s->next[ptr] != ptr + (inverse == true) * -2 + 1)
			return (false);
		ptr = s->next[ptr];
	}
	return (true);
}

//hard coded solver for stack A or B, size 2 and 3.
static inline void	solve_23(t_stack *s, size_t offset,
							 int hmuch, bool target_a)
{
	if (hmuch <= 3 && target_a == true)
	{
		if (s->next[s->a] == offset + 2)
			ra(s);
		else if (s->a == offset + 2)
			rra(s);
		if (s->a == offset + 1)
			sa(s);
	}
	else if (hmuch <= 3 && target_a == false)
	{
		if (s->next[s->b] == offset + 2)
			rb(s);
		else if (s->b == offset + 2)
			rrb(s);
		if (s->b == offset + 1)
			sb(s);
	}
}

//check if 
bool	ps_algorithm_recursion(t_stack *s, size_t ptr,
								size_t len, bool inverse)
{
	(void)s;
	(void)ptr;
	(void)len;
	(void)inverse;
	return (false);
}

void	ps_algorithm(t_stack *s)
{
	if (s->size <= 6)
		solve_23(s, 0, s->size, true);
	(void)s;
}
