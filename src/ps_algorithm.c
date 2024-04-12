/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:47:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/04/12 01:45:24 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"

//some value setting function;
bool 	ps_algorithm(t_ps_stack *a, t_ps_stack *b, unsigned int size)
{
	unsigned int	i;

	ft_memcpy(b->stack, a->stack, size * sizeof(unsigned int));
	a->size = size;
	b->size = size;
	i = -1;
	while (++i < size)
	{
		a->next[i] = 1;
		a->prev[i] = 1;
		b->next[i] = 0;
		b->prev[i] = 0;
	}
	ps_pb(a, b);
	// i = -1;
	// while (++i < size)
	// 	printf("values [%u]:\n\tvalue_A= %u,\tvalue_B= %u,\n\tnext_A=  %u,\tnext_B=  %u,\n\tprev_A=  %u,\tprev_B=  %u;\n", i, \
	// 		   a->stack[i], b->stack[i], a->next[i], b->next[i], a->prev[i], b->prev[i]);
	return (free(a->stack), free(b->stack), free(a->next), free(a->prev), \
			free(b->next), free(b->prev), true);
}
