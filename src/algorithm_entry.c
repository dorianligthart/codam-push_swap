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

void	ps_algorithm(t_stack *s)
{
	(void)s;
}

//Warning: doesn't allow remainder on targeted stack.
static inline void	ps_solve3(t_stack *s, bool target_a)
{
	if (target_a == true)
	{
		if (s->next[s->a] == 2)
			ps_run(s, F_RA);
		else if (s->a == 2)
			ps_run(s, F_RRA);
		if (s->a == 1)
			ps_run(s, F_SA);
	}
	else
	{
		if (s->next[s->b] == 2)
			ps_run(s, F_RB);
		else if (s->b == 2)
			ps_run(s, F_RRB);
		if (s->b == 1)
			ps_run(s, F_SB);
	}
}

void	ps_algorithm_entry(t_stack *s)
{
	if (s->size <= 3)
		ps_solve3(s, true);
	else if (s->size <= 6)
	{
		ps_split_range_a(s, &s->ranges[s->ri], &s->ranges[s->ri + 1]);
		ps_solve3(s, true);
		ps_solve3(s, false);
		ps_run_multiple(s, 3, F_PA, F_PA, F_PA);
	}
	else
	{
		ps_split_range_a_into_3(s,
								&s->ranges[s->ri],
								&s->ranges[s->ri + 1],
								&s->ranges[s->ri + 2]);
		ps_algorithm(s);
	}
}
