/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:34 by doligtha          #+#    #+#             */
/*   Updated: 2024/04/21 00:02:32 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

//O^N^2
//loops through stack, finds the smallest && bigger than index and set to index.
static inline void	ps_normalise(t_ps_stack *s)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	min;
	unsigned int	tmp;

	y = -1;
	while (++y < s->size)
	{
		x = -1;
		min = UINT_MAX;
		while (++x < s->size)
		{
			if ((min > s->stack[x]
				|| (y == s->size - 1 && s->stack[x] == UINT_MAX))
				&& y <= s->stack[x])
			{
				min = s->stack[x];
				tmp = x;
			}
		}
		s->stack[tmp] = y;
	}
}

//int to unsigned int:
//	result = origin + (origin < 0 - INT_MAX - 1) * INT_MIN + INT_MAX + 1;
//eq of:
//	s
static inline bool	ps_parse(char const *argv[], t_ps_stack *s)
{
	unsigned int	x;
	unsigned int	y;

	y = -1;
	while (++y < s->size && argv[y])
	{
		x = -1;
		if (argv[y][0] == '-' && (argv[y][1] >= '0' && argv[y][1] <= '9'))
			x++;
		while (argv[y][++x])
			if (argv[y][x] < '0' || argv[y][x] > '9')
				return (ft_printf("Error: invalid char argv[%u]\n", y), false);
		s->origin[y] = ft_atoi(argv[y]);
		x = -1;
		while (++x < y)
			if (s->origin[x] == s->origin[y])
				return (ft_printf("Error: dup argv[%u-%u]\n", y, x), false);
	}
	y = -1;
	while (++y < s->size)
		s->stack[y] = s->origin[y] \
					+ (s->origin[y] < 0) * INT_MIN \
					+ (s->origin[y] >= 0) * ((unsigned int)INT_MAX + 1);
	return (true);
}

static inline void	ps_free(t_ps_stack *s)
{
	free(s->stack);
	free(s->a_next);
	free(s->a_prev);
	free(s->b_next);
	free(s->b_prev);
	free(s->groups);
	free(s->origin);
}

static inline bool	ps_malloc(t_ps_stack *s, int argc)
{
	s->origin = malloc(argc * sizeof(int));
	if (!s->origin)
		return (false);
	s->stack = malloc(argc * sizeof(unsigned int));
	if (!s->stack)
		return (free(s->origin), false);
	s->groups = malloc(argc * sizeof(unsigned int));
	if (!s->groups)
		return (free(s->origin), free(s->stack), false);
	s->a_next = malloc(argc * sizeof(unsigned int));
	if (!s->a_next)
		return (free(s->origin), free(s->stack), free(s->groups), false);
	s->a_prev = malloc(argc * sizeof(unsigned int));
	if (!s->a_prev)
		return (free(s->origin), free(s->stack), free(s->groups), \
				free(s->a_next), false);
	s->b_next = malloc(argc * sizeof(unsigned int));
	if (!s->b_next)
		return (free(s->origin), free(s->stack), free(s->groups), \
				free(s->a_next), free(s->a_prev), false);
	s->b_prev = malloc(argc * sizeof(unsigned int));
	if (!s->b_prev)
		return (free(s->origin), free(s->stack), free(s->groups), \
				free(s->a_next), free(s->a_prev), free(s->b_next), false);
	return (true);
}

int	main(int argc, char const *argv[])
{
	t_ps_stack	s;

	if (argc < 2)
		return (ft_printf("Error: provide arguments\n"), PS_ERROR);
	argv++;
	argc--;
	if (!ps_malloc(&s, argc))
		return (ft_printf("Error: malloc() failed\n"), PS_ERROR);
	s.size = argc;
	if (!ps_parse(argv, &s))
		return (ps_free(&s), PS_ERROR);
	ps_normalise(&s);
	ps_init(&s);
	ps_free(&s);
	return (0);
}
