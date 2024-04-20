/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:47:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/04/21 00:10:15 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdio.h>

// void	ps_groupgroup()
// {
	
// }

//some value setting function;
void 	ps_init(t_ps_stack *s)
{
	unsigned int	i;

	s->a_ptr = 0;
	s->b_ptr = s->size;
	i = -1;
	while (++i < s->size)
	{
		s->a_next[i] = (i + 1) % s->size;
		s->a_prev[i] = (i - 1) % s->size;
		s->b_next[i] = 0;
		s->b_prev[i] = 0;
	}
}
