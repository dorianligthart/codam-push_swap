/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:34 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/16 17:57:35 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h> //SIZE_MAX

//s->size needs to be set.
static void	ps_init(size_t *src, size_t *prev, size_t *next, t_ps_stack *s)
{
	size_t	i;

	i = -1;
	while (++i < s->size)
	{
		prev[src[i]] = src[i + (i == 0) * s->size - 1];
		next[src[i]] = src[(i + 1) % s->size];
	}
	s->print = false;
	s->fd = 1;
	s->move_count = 0;
	s->a = src[0];
	s->b = SIZE_MAX;
}

//O*N^2
//loops through stack, finds the smallest && bigger than index and set to index.
//messes up data if there are duplicates.
static void	normalise_size(size_t *dst, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	min;
	size_t	tmp;

	tmp = 0;
	y = 0;
	while (y < size)
	{
		x = 0;
		min = SIZE_MAX;
		while (x < size)
		{
			if ((min > dst[x]
				|| (y == size - 1 && dst[x] == SIZE_MAX))
				&& y <= dst[x])
			{
				min = dst[x];
				tmp = x;
			}
			x++;
		}
		dst[tmp] = y;
		y++;
	}
}

static size_t	str_to_uints(const char *str, unsigned int *uint, size_t y)
{
	size_t	x;
	int		tmp;

	while (*str != '\0')
	{
		while (ft_strchr(" \n\v\t\r", *str))
			str++;
		x = (str[0] == '-' && (str[1] >= '0' && str[1] <= '9'));
		if (str[x] < '0' || str[x] > '9')
			return (0);
		tmp = ft_atoi(str);
		uint[y] = tmp + (tmp < 0) * INT_MIN
				+ (tmp >= 0) * ((unsigned int)INT_MAX + 1);
		str += x;
		while (*str >= '0' && *str <= '9')
			str++;
		x = -1;
		while (++x < y)
			if (uint[x] == uint[y])
				return (0);
		y++;
	}
	return (y);
}

//int to unsigned int:
//		result = n + (n < 0 - INT_MAX - 1) * INT_MIN + INT_MAX + 1;
//or	result = n + (n < 0) * INT_MIN + (n >= 0) * ((unsigned int)INT_MAX + 1);
static int	main2(unsigned int *uints, t_ps_stack *s)
{
	size_t	*prev;
	size_t	*next;
	size_t	*src;
	size_t	i;

	src = (size_t *)malloc(s->size * sizeof(size_t));
	if (src == NULL)
		return (free(uints), PS_ERROR);
	i = -1;
	while (++i < s->size)
		src[i] = (size_t)uints[i];
	free(uints);
	normalise_size(src, s->size);
	prev = (size_t *)malloc((2 * s->size) * sizeof(size_t));
	if (prev == NULL)
		return (free(src), PS_ERROR);
	next = prev + s->size;
	ps_init(src, prev, next, s);
	s->funcseq = (unsigned char *)src;
	for (size_t z = 0; z < s->size; z++) printf("%zu, ", src[z]);
	ps_algorithm(prev, next, s);
	free(src);
	free(prev);
	return (PS_SUCCESS);
}

//gotta love bash!        `./program arg1 arg2 arg3`
//is abs not the same as: `./program "arg1 arg2 arg3"`
int	main(int argc, char const **argv)
{
	t_ps_stack		stack;
	int				i;
	unsigned int	*uints;

	if (argc < 2)
		return (ft_printf("Error.\n"), PS_ERROR);
	argv++;
	argc--;
	stack.size = 0;
	i = -1;
	while (++i < argc)
		stack.size += ft_countwords(argv[i], " \n\v\t\r");
	uints = (unsigned int *)malloc(stack.size * sizeof(unsigned int));
	if (!uints)
		return (PS_ERROR);
	stack.a = 0;
	i = -1;
	while (++i < argc)
	{
		stack.a = str_to_uints(argv[i], uints, stack.a);
		if (stack.a == 0)
			return (free(uints), PS_ERROR);
	}
	return (main2(uints, &stack));
}
