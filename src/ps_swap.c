/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:24:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 10:30:33 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdint.h>

bool	ps_sa(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp;

	if (stack->a != SIZE_MAX && next[stack->a] != stack->a)
	{
		tmp = next[next[stack->a]];
		next[prev[stack->a]] = next[stack->a];
		prev[next[next[stack->a]]] = stack->a;
		next[next[stack->a]] = stack->a;
		prev[next[stack->a]] = prev[stack->a];
		prev[stack->a] = next[stack->a];
		next[stack->a] = tmp;
		if (-1 == write(1, "sa\n", 3))
			return (false);
		stack->total_move_count++;
	}
	return (true);
}

bool	ps_sb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp;

	if (stack->b != SIZE_MAX && next[stack->b] != stack->b)
	{
		tmp = next[next[stack->b]];
		prev[next[next[stack->b]]] = stack->b;
		next[prev[stack->b]] = next[stack->b];
		prev[next[stack->b]] = prev[stack->b];
		next[next[stack->b]] = stack->b;
		prev[stack->b] = next[stack->b];
		next[stack->b] = tmp;
		if (-1 == write(1, "sb\n", 3))
			return (false);
		stack->total_move_count++;
	}
	return (true);
}

bool	ps_ss(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp;

	if ((stack->a != SIZE_MAX && next[stack->a] != stack->a)
		&& (stack->b != SIZE_MAX && next[stack->b] != stack->b))
	{
		tmp = next[next[stack->a]];
		prev[next[next[stack->a]]] = stack->a;
		next[prev[stack->a]] = next[stack->a];
		prev[next[stack->a]] = prev[stack->a];
		next[next[stack->a]] = stack->a;
		prev[stack->a] = next[stack->a];
		next[stack->a] = tmp;
		tmp = next[next[stack->b]];
		prev[next[next[stack->b]]] = stack->b;
		next[prev[stack->b]] = next[stack->b];
		next[next[stack->b]] = stack->b;
		prev[next[stack->b]] = prev[stack->b];
		prev[stack->b] = next[stack->b];
		next[stack->b] = tmp;
		stack->total_move_count++;
		if (-1 == write(1, "ss\n", 3))
			return (false);
	}
	return (true);
}

//SWAP: ptr X = 1;
//TMP     = D;
//prev[D] = B; 		->		prev[next[next[ptr]]] = ptr;
//next[A] = C; 		->		next[prev[ptr]] = next[ptr];
//next[C] = B; 		->		next[next[ptr]] = ptr;
//prev[C] = A; 		->		prev[next[ptr]] = prev[ptr];
//prev[B] = C; 		->		prev[ptr] = next[ptr];
//next[B] = D; 		->		next[ptr] = TMP;

//stackA ptr++ 		->		X = next[ptr];