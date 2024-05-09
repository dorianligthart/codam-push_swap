/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:24:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 01:23:07 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

bool	ps_pa(t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "pa\n", 3))
		return (false);
	return (true);
}

bool	ps_pb(t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "pb\n", 3))
		return (false);
	return (true);
}

bool	ps_sa (t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "sa\n", 3))
		return (false);
	return (true);
}

bool	ps_sb (t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "sb\n", 3))
		return (false);
	return (true);
}

bool	ps_ss (t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "ss\n", 3))
		return (false);
	return (true);
}
