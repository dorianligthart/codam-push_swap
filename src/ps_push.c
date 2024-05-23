/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 04:44:59 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/16 17:43:29 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "pushswap.h"

static inline void ps_norminette_push(size_t *prev, size_t *next,
									  size_t stackx, size_t tmp2)
{
	prev[tmp2] = prev[stackx];
	next[tmp2] = stackx;
	next[prev[stackx]] = tmp2;
	prev[next[stackx]] = tmp2;
	stackx = tmp2;
}

bool	ps_pa(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[3];

	if (stack->a != SIZE_MAX)
	{
		tmp[0] = prev[stack->a];
		tmp[1] = next[stack->a];
		tmp[2] = stack->a;
		stack->a = next[stack->a];
		if (stack->a == tmp[2])
			stack->a = SIZE_MAX;
		next[tmp[0]] = tmp[1];
		prev[tmp[1]] = tmp[0];
		if (stack->b == SIZE_MAX)
			stack->b = tmp[2];
		else
			ps_norminette_push(prev, next, stack->b, tmp[2]);
		if (stack->print == true)
		{
			stack->move_count++;
			if (write(stack->fd, "pa\n", 3) == -PS_ERROR)
				return (false);
		}
	}
	return (true);
}

bool	ps_pb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[3];

	if (stack->b != SIZE_MAX)
	{
		tmp[0] = prev[stack->b];
		tmp[1] = next[stack->b];
		tmp[2] = stack->b;
		stack->b = next[stack->b];
		if (stack->b == tmp[2])
			stack->b = SIZE_MAX;
		next[tmp[0]] = tmp[1];
		prev[tmp[1]] = tmp[0];
		if (stack->a == SIZE_MAX)
			stack->a = tmp[2];
		else
			ps_norminette_push(prev, next, stack->a, tmp[2]);
		if (stack->print == true)
		{
			stack->move_count++;
			if (write(stack->fd, "pa\n", 3) == -PS_ERROR)
				return (false);
		}
	}
	return (true);
}
