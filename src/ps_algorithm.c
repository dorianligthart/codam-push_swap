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
#include <stdint.h>

void	ps_printstacks(size_t *next, t_ps_stack *stack, size_t ptr)
{
	ft_printf("stack %c[HEAD=%u]: ", (ptr == stack->a) ? 'A' : 'B', ptr);
	if (ptr != SIZE_MAX)
	{
		ft_printf("%u,  ", (unsigned int)ptr);
		ptr = next[ptr];
		while (ptr != stack->a && ptr != stack->b)
		{
			ft_printf("%u,  ", (unsigned int)ptr);
			ptr = next[ptr];
		}
	}
}

//some value setting function;
//	- b initialised as SIZE_MAX meaning it's empty;
bool	ps_algorithm(size_t *prev, size_t *next, t_ps_stack *stack)
{
	// printf("\n", );
	(void)prev;
	(void)next;
	(void)stack;
	// stack->a = stack->size - 1;
	// ps_ra(prev, next, stack);
	// ps_ra(prev, next, stack);
	ps_sa(prev, next, stack);
	// ps_sa(prev, next, stack);
	// ps_printstacks(next, stack, stack->a);
	return (true);
}
