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

void	ps_printstack(size_t ptr, t_stack *stack)
{
	if (ptr == stack->a)
		ft_printf("%c[HEAD, ", 'A');
	else if (ptr == stack->b)
		ft_printf("%c[HEAD, ", 'B');
	else
		ft_printf("%c[HEAD, ", 'X');
	if (ptr != SIZE_MAX)
	{
		ft_printf("%u, ", (unsigned int)ptr);
		ptr = stack->next[ptr];
		while (ptr != stack->a && ptr != stack->b)
		{
			ft_printf("%u, ", (unsigned int)ptr);
			ptr = stack->next[ptr];
		}
	}
	else
		ft_printf("EMPTY, ");
	ft_printf("TAIL]\n");
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

static int	main2(unsigned int *uints, t_stack *stack)
{
	size_t	*array;
	size_t	i;

	array = (size_t *)malloc(stack->size * sizeof(size_t));
	if (array == NULL)
		return (free(uints), PS_ERROR);
	i = -1;
	while (++i < stack->size)
		array[i] = (size_t)uints[i];
	free(uints);
	normalise_size(array, stack->size);
	i = -1;
	while (++i < stack->size)
	{
		stack->prev[array[i]] = array[i + (i == 0) * stack->size - 1];
		stack->next[array[i]] = array[(i + 1) % stack->size];
	}
	stack->prev = (size_t *)malloc((2 * stack->size) * sizeof(size_t));
	if (stack->prev == NULL)
		return (free(array), PS_ERROR);
	stack->next = stack->prev + stack->size;
	stack->a = array[0];
	stack->fseq = (unsigned char *)array;
	ps_printstack(stack->a, stack);
	ps_printstack(stack->b, stack);
	ps_algorithm_init(stack);
	ps_printstack(stack->a, stack);
	ps_printstack(stack->b, stack);
	return (free(array), free(stack->prev), PS_SUCCESS);
}

//gotta love bash!        `./program arg1 arg2 arg3`
//is abs not the same as: `./program "arg1 arg2 arg3"`
int	main(int argc, char const **argv)
{
	t_stack			stack;
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
