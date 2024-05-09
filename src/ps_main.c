/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:34 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 03:29:26 by doligtha         ###   ########.fr       */
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
void	ps_normalise(size_t *dst, size_t size)
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
//return false when 
bool	ps_array2dcll(size_t *prev, size_t *next, size_t *src, size_t *size)
{
	size_t	head;
	size_t	x;
	size_t	y;

	ps_normalise(src, *size);
	head = src[0];
	x = 0;
	y = 0;
	while (x < *size)
	{
		//TODO: decide on data struct, see header!
		prev[x] = src[x];
		next[x] = src[x];
	}
	*size = head;
	return (true);
}

// return false on duplicate.
bool	ft_argv_to_int(size_t argc, char const *argv[], int *src)
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
	return (true);
}


//int to unsigned int:
//		result = n + (n < 0 - INT_MAX - 1) * INT_MIN + INT_MAX + 1;
//or	result = n + (n < 0) * INT_MIN + (n >= 0) * ((unsigned int)INT_MAX + 1);
static int	main2(size_t argc, char const *argv[])
{
	t_dcllist	s;
	int			*src;
	size_t		*dst;
	size_t		i;

	src = (int *)malloc(argc * sizeof(int));
	if (src == NULL)
		return (PS_ERROR);
	dst = (size_t *)malloc(argc * 4 * sizeof(size_t));
	if (dst == NULL)
		return (free(src), PS_ERROR);
	s.next = dst + argc;
	s.prev = dst + (argc * 2);
	if (false == ft_argv_to_int(argc, argv, src))
		return (free(src), free(dst), PS_ERROR);
	i = -1;
	while (++i < argc)
		dst[i] = src[i] + ((src[i] < 0) - INT_MIN) * INT_MIN + INT_MAX + 1;
	i = ps_array2dcll(s.prev, s.next, dst, &argc);
	if (false == ps_algorithm(&s, i))
		return (free(src), free(dst), PS_ERROR);
	return (free(src), free(dst), PS_SUCCESS);
}

//gotta love bash!  `./program arg1 arg2 arg3`
//		is abs not: `./program "arg1 arg2 arg3"`
//Q: Do I support one or the other, or both?
//A: First one works, second one: ft_split_with_delims() isn't implemented yet.
int	main(int argc, char const *argv[])
{
	bool	one_arg;
	size_t	argcsize;
	int		tmp;

	if (argc < 2)
		return (write(1, "Error: provide arguments!\n", 26), PS_ERROR);
	argv++;
	argc--;
	argcsize = ((argc >= 0) * 2 - 1) * argc;
	one_arg = false;
	if (argcsize == 1)
	{
		one_arg = true;
		argv = (char const **)ft_split_with_delims(argv[1], " \f\n\r\t\v");
		if (argv == NULL)
			return (write(1, "Error: malloc failure\n", 22), PS_ERROR);
		argcsize = 0;
		while (argv[argcsize] != NULL)
			argcsize++;
	}
	tmp = main2(argcsize, argv);
	if (one_arg == true)
		return (ft_free((void *)argv), free((void *)argv), tmp);
	return (tmp);
}
