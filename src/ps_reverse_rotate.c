/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:27:55 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 05:10:23 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

bool	ps_rra(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	(void)next;
	(void)stack;
	if (-1 == write(1, "rra\n", 4))
		return (false);
	return (true);
}

bool	ps_rrb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	(void)next;
	(void)stack;
	if (-1 == write(1, "rrb\n", 4))
		return (false);
	return (true);
}

bool	ps_rrr(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	(void)next;
	(void)stack;	
	if (-1 == write(1, "rrr\n", 4))
		return (false);
	return (true);
}
