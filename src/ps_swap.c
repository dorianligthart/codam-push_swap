/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:24:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/16 18:16:46 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdint.h>

//SWAP:
//suppose 4 'nodes':	A B C D
//and swapping B and C (HEAD=1);
//						A C B D
//TMP     = D;
//prev[D] = B; 		->		prev[next[next[ptr]]] = ptr;
//next[A] = C; 		->		next[prev[ptr]] = next[ptr];
//next[C] = B; 		->		next[next[ptr]] = ptr;
//prev[C] = A; 		->		prev[next[ptr]] = prev[ptr];
//prev[B] = C; 		->		prev[ptr] = next[ptr];
//next[B] = D; 		->		next[ptr] = TMP;

//stackA ptr++ 		->		X = next[ptr];
bool	ps_sa(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[PS_COUNT];

	if (stack->a != SIZE_MAX && next[stack->a] != stack->a)
	{
		tmp[PS_A] = prev[stack->a];
		tmp[PS_B] = stack->a;
		tmp[PS_C] = next[stack->a];
		tmp[PS_D] = next[next[stack->a]];
		prev[tmp[PS_D]] = tmp[PS_B];
		next[tmp[PS_A]] = tmp[PS_C];
		next[tmp[PS_B]] = tmp[PS_D];
		prev[tmp[PS_C]] = tmp[PS_A];
		prev[tmp[PS_B]] = tmp[PS_C];
		next[tmp[PS_C]] = tmp[PS_B];
		stack->a = prev[stack->a];
		if (-1 == write(1, "sa\n", 3))
			return (false);
		stack->total_move_count++;
	}
	return (true);
}

bool	ps_sb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[PS_COUNT];

	if (stack->b != SIZE_MAX && next[stack->b] != stack->b)
	{
		tmp[PS_A] = prev[stack->b];
		tmp[PS_B] = stack->b;
		tmp[PS_C] = next[stack->b];
		tmp[PS_D] = next[next[stack->b]];
		prev[tmp[PS_D]] = tmp[PS_B];
		next[tmp[PS_A]] = tmp[PS_C];
		next[tmp[PS_B]] = tmp[PS_D];
		prev[tmp[PS_C]] = tmp[PS_A];
		prev[tmp[PS_B]] = tmp[PS_C];
		next[tmp[PS_C]] = tmp[PS_B];
		stack->b = prev[stack->b];
		if (-1 == write(1, "sb\n", 3))
			return (false);
		stack->total_move_count++;
	}
	return (true);
}

static inline void	ps_ss2(size_t *prev, size_t *next,\
						   t_ps_stack *stack, size_t *tmp)
{
	tmp[PS_A] = prev[stack->a];
	tmp[PS_B] = stack->a;
	tmp[PS_C] = next[stack->a];
	tmp[PS_D] = next[next[stack->a]];
	prev[tmp[PS_D]] = tmp[PS_B];
	next[tmp[PS_A]] = tmp[PS_C];
	next[tmp[PS_B]] = tmp[PS_D];
	prev[tmp[PS_C]] = tmp[PS_A];
	prev[tmp[PS_B]] = tmp[PS_C];
	next[tmp[PS_C]] = tmp[PS_B];
	stack->a = prev[stack->a];
	tmp[PS_A] = prev[stack->b];
	tmp[PS_B] = stack->b;
	tmp[PS_C] = next[stack->b];
	tmp[PS_D] = next[next[stack->b]];
	prev[tmp[PS_D]] = tmp[PS_B];
	next[tmp[PS_A]] = tmp[PS_C];
	next[tmp[PS_B]] = tmp[PS_D];
	prev[tmp[PS_C]] = tmp[PS_A];
	prev[tmp[PS_B]] = tmp[PS_C];
	next[tmp[PS_C]] = tmp[PS_B];
	stack->b = prev[stack->b];
}

bool	ps_ss(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[PS_COUNT];

	if ((stack->a != SIZE_MAX && next[stack->a] != stack->a)
		&& (stack->b != SIZE_MAX && next[stack->b] != stack->b))
	{
		ps_ss2(prev, next, stack, tmp);
		if (-1 == write(1, "ss\n", 3))
			return (false);
		stack->total_move_count++;
	}
	return (true);
}
