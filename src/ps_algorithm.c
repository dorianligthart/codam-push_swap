/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:47:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 10:11:44 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdint.h>

void	ps_printstacks(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t ptr;

	(void)prev;
	printf("A_HEAD = %zu\n", stack->a);
	ptr = stack->a;
	while (ptr != SIZE_MAX && next[ptr] != ptr)
	{
		printf("[");
		printf("%zu, ", ptr);
		printf("%zu, ", next[ptr]);
		printf("%zu", prev[ptr]);
		printf("]\n");
		ptr = next[ptr];
	}
}

//some value setting function;
//	- b initialised as SIZE_MAX meaning it's empty;
bool	ps_algorithm(size_t *prev, size_t *next, t_ps_stack *stack)
{
	stack->b = SIZE_MAX;
	stack->a = 1;
	// stack->a = stack->size - 1;
	ps_sa(prev, next, stack);
	// ps_printstacks(prev, next, stack);
	return (true);
}
