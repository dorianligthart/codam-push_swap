/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:26:58 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/16 14:21:47 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

bool	ps_ra(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	stack->a = next[stack->a];
	if (stack->print == true)
	{
		stack->move_count++;
		if (write(stack->fd, "ra\n", 3) == -PS_ERROR)
			return (false);
	}
	return (true);
}

bool	ps_rb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	stack->b = next[stack->b];
	if (stack->print == true)
	{
		stack->move_count++;
		if (write(stack->fd, "rb\n", 3) == -PS_ERROR)
			return (false);
	}
	return (true);
}

bool	ps_rr(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	stack->a = next[stack->a];
	stack->b = next[stack->b];
	if (stack->print == true)
	{
		stack->move_count++;
		if (write(stack->fd, "rr\n", 3) == -PS_ERROR)
			return (false);
	}
	return (true);
}
