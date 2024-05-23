/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:27:55 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/16 17:43:12 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

bool	ps_rra(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)next;
	stack->a = prev[stack->a];
	if (stack->print == true)
	{
		stack->move_count++;
		if (write(stack->fd, "rra\n", 4) == -PS_ERROR)
			return (false);
	}
	return (true);
}

bool	ps_rrb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)next;
	stack->b = prev[stack->b];
	if (stack->print == true)
	{
		stack->move_count++;
		if (write(stack->fd, "rrb\n", 4) == -PS_ERROR)
			return (false);
	}
	return (true);
}

bool	ps_rrr(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)next;
	stack->b = prev[stack->b];
	stack->a = prev[stack->a];
	if (stack->print == true)
	{
		stack->move_count++;
		if (write(stack->fd, "rrr\n", 4) == -PS_ERROR)
			return (false);
	}
	return (true);
}
