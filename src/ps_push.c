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

static inline void	ps_insert_item_to_stack(size_t *prev, size_t *next, \
											size_t item, size_t *tmp)
{
	if (item == SIZE_MAX)
		item = tmp[2];
	else
	{
		next[tmp[2]] = next[item];
		prev[tmp[2]] = prev[item];
		next[prev[item]] = tmp[2];
		prev[next[item]] = tmp[2];
	}
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
		ps_insert_item_to_stack(prev, next, stack->b, tmp);
		if (stack->print == true)
		{
			stack->total_move_count++;
			if (write(stack->fd, "pa\n", 3) == -PS_ERROR)
				return (false);
		}
	}
	return (true);
}

bool	ps_pb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	(void)next;
	(void)stack;
	return (true);
}
