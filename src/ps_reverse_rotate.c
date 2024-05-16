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
	if (-1 == write(1, "rra\n", 4))
		return (false);
	stack->total_move_count++;
	return (true);
}

bool	ps_rrb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)next;
	stack->b = prev[stack->b];
	if (-1 == write(1, "rrb\n", 4))
		return (false);
	stack->total_move_count++;
	return (true);
}

bool	ps_rrr(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)next;
	stack->b = prev[stack->b];
	stack->a = prev[stack->a];
	if (-1 == write(1, "rrr\n", 4))
		return (false);
	stack->total_move_count++;
	return (true);
}
