/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 04:44:59 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 10:24:15 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

bool	ps_pa(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	(void)next;
	(void)stack;
	if (-1 == write(1, "pa\n", 3))
		return (false);
	return (true);
}

bool	ps_pb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	(void)prev;
	(void)next;
	(void)stack;
	if (-1 == write(1, "pb\n", 3))
		return (false);
	return (true);
}
