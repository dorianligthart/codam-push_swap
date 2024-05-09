/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:34 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 09:10:59 by doligtha         ###   ########.fr       */
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

//O^N^2
//loops through stack, finds the smallest && bigger than index and set to index.
//messes up data if there are duplicates.
static void	normalise_size(size_t *dst, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	min;
	size_t	tmp;

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

//links indexes together using 2 'next' and 'previous' arrays.
//Values in src, will be used as indexes in next and prev,
//sets HEAD of converted stack to *size;
//returns false on error;
static bool	size_to_linked_list_array(size_t *prev, size_t *next,\
                                      size_t *src, t_ps_stack *stack)
{
	size_t	x;
	size_t	y;

	stack->a = src[0];
	normalise_size(src, stack->size);
	x = 0;
	y = 0;
	while (x < stack->size)
	{
		prev[x] = x + (x == 0) * stack->size - 1;
		next[x] = (x + 1) % stack->size;
		x++;
	}
	return (true);
}

// return false on duplicate/invalid character [0-9\-]
static bool	argv_to_int_to_size(size_t argc, char const *argv[],\
                                  int *src, size_t *dst)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < argc && argv[y])
	{
		x = -1;
		if (argv[y][0] == '-' && (argv[y][1] >= '0' && argv[y][1] <= '9'))
			x++;
		while (argv[y][++x])
			if (argv[y][x] < '0' || argv[y][x] > '9')
				return (ft_printf("Error: invalid char argv[%u]\n", y), false);
		src[y] = ft_atoi(argv[y]);
		x = -1;
		while (++x < y)
			if (src[x] == src[y])
				return (ft_printf("Error: dup argv[%i-%i]\n", y, x), false);
	}
	y = -1;
	while (++y < argc)
		dst[y] = src[y] + (src[y] < 0) * INT_MIN + (src[y] >= 0) * ((unsigned int)INT_MAX + 1);
	return (true);
}


//int to unsigned int:
//		result = n + (n < 0 - INT_MAX - 1) * INT_MIN + INT_MAX + 1;
//or	result = n + (n < 0) * INT_MIN + (n >= 0) * ((unsigned int)INT_MAX + 1);
static int	main2(size_t argc, char const *argv[])
{
	int			*src;
	size_t		*dst;
	size_t		*next;
	size_t		*prev;
	t_ps_stack	stack;

	src = (int *)malloc(argc * sizeof(int));
	if (src == NULL)
		return (PS_ERROR);
	dst = (size_t *)malloc(argc * 3 * sizeof(size_t));
	if (dst == NULL)
		return (free(src), PS_ERROR);
	prev = dst + argc;
	next = dst + argc * 2;
	stack.size = argc;
	if (false == argv_to_int_to_size(argc, argv, src, dst)
		|| false == size_to_linked_list_array(prev, next, dst, &stack)
		|| false == ps_algorithm(prev, next, &stack))
		return (free(src), free(dst), PS_ERROR);
	for (size_t i = 0; i < argc; i++) printf("%zu ", dst[i]);
	printf(" = dst[]\n");
	for (size_t i = 0; i < argc; i++) printf("%zu ", next[i]);
	printf(" = next[]\n2 3 1 4 5 6 0\n");
	for (size_t i = 0; i < argc; i++) printf("%zu ", prev[i]);
	printf(" = prev[]\n6 2 0 1 3 4 5\n");
	return (free(src), free(dst), PS_SUCCESS);
}

//gotta love bash!  `./program arg1 arg2 arg3`
//		is abs not: `./program "arg1 arg2 arg3"`
//Q: Do I support one or the other, or both?
//A: First one works, second one: ft_split_with_delims() isn't implemented yet.
int	main(int argc, char const *argv[])
{
	bool	one_arg;
	size_t	argcount;
	int		tmp;

	if (argc < 2)
		return (write(1, "Error: provide arguments!\n", 26), PS_ERROR);
	argv++;
	argc--;
	argcount = ((argc >= 0) * 2 - 1) * argc;
	one_arg = false;
	if (argcount == 1)
	{
		one_arg = true;
		argv = (char const **)ft_split_with_delims(argv[1], " \f\n\r\t\v");
		if (argv == NULL)
			return (write(1, "Error: malloc failure\n", 22), PS_ERROR);
		argcount = 0;
		while (argv[argcount] != NULL)
			argcount++;
	}
	tmp = main2(argcount, argv);
	if (one_arg == true)
		return (ft_free((void *)argv), free((void *)argv), tmp);
	return (tmp);
}
