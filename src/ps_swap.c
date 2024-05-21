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
bool	ps_sa(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[2];

	if (stack->a != SIZE_MAX && next[stack->a] != stack->a)
	{
		tmp[0] = stack->a;
		tmp[1] = next[stack->a];
		prev[next[next[stack->a]]] = tmp[0];
		next[tmp[0]] = next[next[stack->a]];
		next[prev[stack->a]] = tmp[1];
		prev[tmp[1]] = prev[stack->a];
		prev[tmp[0]] = tmp[1];
		next[tmp[1]] = tmp[0];
		stack->a = prev[stack->a];
		if (stack->print == true)
		{
			stack->total_move_count++;
			if (write(1, "sa\n", 3) == -PS_ERROR)
				return (false);
		}
	}
	return (true);
}

bool	ps_sb(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[2];

	if (stack->b != SIZE_MAX && next[stack->b] != stack->b)
	{
		tmp[0] = stack->b;
		tmp[1] = next[stack->b];
		prev[next[next[stack->b]]] = tmp[0];
		next[tmp[0]] = next[next[stack->b]];
		next[prev[stack->b]] = tmp[1];
		prev[tmp[1]] = prev[stack->b];
		prev[tmp[0]] = tmp[1];
		next[tmp[1]] = tmp[0];
		stack->b = prev[stack->b];
		if (stack->print == true)
		{
			stack->total_move_count++;
			if (write(1, "sb\n", 3) == -PS_ERROR)
				return (false);
		}
	}
	return (true);
}

static inline void	ps_ss2(size_t *prev, size_t *next,\
						   t_ps_stack *stack, size_t *tmp)
{
	tmp[0] = stack->a;
	tmp[1] = next[stack->a];
	prev[next[next[stack->a]]] = tmp[0];
	next[tmp[0]] = next[next[stack->a]];
	next[prev[stack->a]] = tmp[1];
	prev[tmp[1]] = prev[stack->a];
	prev[tmp[0]] = tmp[1];
	next[tmp[1]] = tmp[0];
	stack->a = prev[stack->a];
	tmp[0] = stack->b;
	tmp[1] = next[stack->b];
	prev[next[next[stack->b]]] = tmp[0];
	next[tmp[0]] = next[next[stack->b]];
	next[prev[stack->b]] = tmp[1];
	prev[tmp[1]] = prev[stack->b];
	prev[tmp[0]] = tmp[1];
	next[tmp[1]] = tmp[0];
	stack->b = prev[stack->b];
}

bool	ps_ss(size_t *prev, size_t *next, t_ps_stack *stack)
{
	size_t	tmp[2];

	if ((stack->a != SIZE_MAX && next[stack->a] != stack->a)
		&& (stack->b != SIZE_MAX && next[stack->b] != stack->b))
	{
		ps_ss2(prev, next, stack, tmp);
		if (stack->print == true)
		{
			stack->total_move_count++;
			if (write(1, "ss\n", 3) == -PS_ERROR)
				return (false);
		}
	}
	return (true);
}
