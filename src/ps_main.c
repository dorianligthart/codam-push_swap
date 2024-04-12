/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:34 by doligtha          #+#    #+#             */
/*   Updated: 2024/04/12 01:43:34 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

// #include "pushswap.h"
#include "libft.h"

//step 2:
//O^N through a stack. and find smallest but bigger than index and set to index.
static inline void	ps_normalise_stack(unsigned int *stack, \
									   unsigned int size)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	min;
	unsigned int	tmp;

	i = -1;
	while (++i < size)
	{
		k = -1;
		min = UINT_MAX;
		while (++k < size)
		{
			if ((min > stack[k] || (i == size - 1 && stack[k] == UINT_MAX))
				&& i <= stack[k])
			{
				min = stack[k];
				tmp = k;
			}
		}
		stack[tmp] = i;
	}
}

//step 1:	int's:				to	unsigned int's:
//			map INT_MIN ... -1  to	0 ... INT_MAX
//			map 0 ... INT_MAX   to	(INT_MAX + 1) ... UINT_MAX
static inline void	ps_normalise_set_stack(int **integers, \
						unsigned int *stack, unsigned int size)
{
	unsigned int	i;
	
	i = -1;
	while (++i < size)
	{
		if ((*integers)[i] >= 0)
			stack[i] = (unsigned int)(*integers)[i] + INT_MAX + 1;
		else	
			stack[i] = (unsigned int)(*integers)[i] + INT_MIN;
	}
	ps_normalise_stack(stack, size);
}

static inline bool	ps_parse(int argc, char const *argv[], int **integers)
{
	int	x;
	int	y;

	(*integers) = malloc(argc * sizeof(int));
	if (!(*integers))
		return (false);
	y = -1;
	while (++y < argc && argv[y])
	{
		x = -1;
		if (argv[y][0] == '-' && (argv[y][1] >= '0' && argv[y][1] <= '9'))
			x++;
		while (argv[y][++x])
			if (argv[y][x] < '0' || argv[y][x] > '9')
				return (false);
		(*integers)[y] = ft_atoi(argv[y]);
		x = -1;
		while (++x < y)
			if ((*integers)[x] == (*integers)[y])
				return (false);
	}
	return (true);
}

static inline bool	ps_malloc(t_ps_stack *a, t_ps_stack *b,
							  int **integers, int argc)
{
	integers = malloc(argc * sizeof(int));
	if (!integers)
		return (false);
	a->stack = malloc(argc * sizeof(unsigned int));
	if (!a->stack)
		return (free(integers), false);
	b->stack = malloc(argc * sizeof(unsigned int));
	if (!b->stack)
		return (free(integers), free(a->stack), false);
	a->next = malloc(argc * sizeof(unsigned int));
	if (!a->next)
		return (free(integers), free(a->stack), free(b->stack), false);
	a->prev = malloc(argc * sizeof(unsigned int));
	if (!a->prev)
		return (free(integers), free(a->stack), free(b->stack), free(a->next), \
				false);
	b->next = malloc(argc * sizeof(unsigned int));
	if (!b->next)
		return (free(integers), free(a->stack), free(b->stack), free(a->next), \
				free(a->prev), false);
	b->prev = malloc(argc * sizeof(unsigned int));
	if (!b->prev)
		return (free(integers), free(a->stack), free(b->stack), free(a->next), \
				free(a->prev), free(b->next), false);
	return (true);
}

int	main(int argc, char const *argv[])
{
	t_ps_stack	a;
	t_ps_stack	b;
	int			*integers;

	if (argc < 2)
		return (ft_printf("Error\n"), 1);
	argv++;
	argc--;
	if (!ps_malloc(&a, &b, &integers, argc))
		return (ft_printf("Error\n"), 1);
	if (!ps_parse(argc, argv, &integers))
		return (ft_printf("Error\n"), 1);
	ps_normalise_set_stack(&integers, a.stack, argc);
	free(integers);
	if (!ps_algorithm(&a, &b, (unsigned int)argc))
		return (ft_printf("Error\n"), 1);
	return (0);
}
