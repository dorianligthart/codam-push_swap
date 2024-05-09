/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:26:58 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 01:23:15 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

bool ps_ra(t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "ra\n", 3))
		return (false);
	return (true);
}

bool ps_rb(t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "rb\n", 3))
		return (false);
	return (true);
}

bool ps_rr(t_dcllist *s)
{
	(void)s;
	if (-1 == write(1, "rr\n", 3))
		return (false);
	return (true);
}
