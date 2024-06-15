/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:50:53 by doligtha          #+#    #+#             */
/*   Updated: 2024/06/15 08:23:11 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

//throughout the program higher range is always targeted to be highest.
void	ps_split_range_2a(t_stack *s, t_range *initial, t_range *higher)
{
	size_t	len;

	len = initial->max - initial->min + 1;

	higher->min = initial->min + len / 2 + len % 2 - 1;
	higher->max = initial->max;
	
	initial->max = initial->min + len / 2 + len % 2;
	initial->min = initial->min;

	while (len--)
	{
		if (s->a <= initial->max)
			ps_run(s, F_PB);
		if (s->a >= higher->min)
			ps_run(s, F_RA);
	}
	s->ri += 1;
	// printf("initial->min=%zu, initial->max=%zu\n", initial->min, initial->max);
	// printf("higher->min=%zu, higher->max=%zu\n", higher->min, higher->max);
}

//only done one time, it's the first move to divide stack A digits to 3 ranges.
void	ps_split_range_3a(t_stack *s, t_range *initial,
						  t_range *middle, t_range *higher)
{
	size_t	len;

	len = s->ranges[s->ri].max - s->ranges[s->ri].min + 1;
	
	higher->max = initial->max;
	higher->min = initial->min + len / 3 * 2 + len % 3 - 1;

	middle->max = initial->min + len / 3 * 2 + len % 3;
	middle->min = initial->min + len / 3 - 1; 
	
	initial->max = initial->min + len / 3;
	initial->min = initial->min; 
	while (len--)
	{
		if (s->a <= initial->max)
			ps_run(s, F_PA);
		if (s->a >= middle->min && s->a <= middle->max)
			ps_run_multiple(s, 2, F_PA, F_RRB);
		if (s->a >= higher->min)
			ps_run(s, F_RA);
	}
	s->ri += 2;
}

void	ps_algorithm(t_stack *s)
{
	(void)s;
}
