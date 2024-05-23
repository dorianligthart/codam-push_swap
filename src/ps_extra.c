/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:31:21 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/21 15:07:16 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"

void	ps_printstack(size_t *next, t_stack *stack, size_t ptr)
{
	if (ptr == stack->a)
		ft_printf("%c[HEAD, ", 'A');
	else if (ptr == stack->b)
		ft_printf("%c[HEAD, ", 'B');
	else
		ft_printf("%c[HEAD, ", 'x');
	if (ptr != SIZE_MAX)
	{
		ft_printf("%u, ", (unsigned int)ptr);
		ptr = next[ptr];
		while (ptr != stack->a && ptr != stack->b)
		{
			ft_printf("%u, ", (unsigned int)ptr);
			ptr = next[ptr];
		}
	}
	ft_printf("TAIL]\n");
}

//not really the actual cost but a good indicator;
size_t	ps_getcost(size_t *prev, size_t *next, t_stack *stack)
{
	size_t	cost;
	size_t	ui;

	(void)prev;
	(void)stack;
	cost = 0;
	ui = 0;
	while (next[ui])
	{
		if (ui < SIZE_MAX - ui)
		{
			if (ui >= next[ui])
				cost += (ui - next[ui]) * 2;
			else
				cost += (next[ui] - ui) * 2;
		}
	}
	return (cost);
}
