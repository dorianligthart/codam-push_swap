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


static int	ps_main3(t_stack *stack)
{
	void (*fptrs[F_COUNT])(t_stack *) 
		= {NULL, sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr};
	const char *foutput[F_COUNT]
		= {NULL, "sa\n", "sb\n", "ss\n", "pa\n", "pb\n",
		"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};
	const int foutputlen[F_COUNT]
		= {0, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4};
	const int fundo[F_COUNT]
		= {0, 1, 2, 3, 5, 4, 9, 10, 11, 6, 7, 8};

	stack->fptrs = fptrs;
	stack->foutput = foutput;
	stack->foutputlen = foutputlen;
	stack->fundo = fundo;


	ps_algorithm_entry(stack);
	return (ps_write_fseq(stack));
}

static int	main2(size_t *uints, t_stack *stack)
{
	size_t	i;
	int		returnval;

	ft_normalise_size(uints, stack->size);
	stack->prev = (size_t *)malloc((2 * stack->size) * sizeof(size_t));
	if (stack->prev == NULL)
		return (free(uints), ft_printf("Error\n"), EXIT_ERROR);
	stack->next = stack->prev + stack->size;
	i = -1;
	while (++i < stack->size)
	{
		stack->prev[uints[i]] = uints[i + (i == 0) * stack->size - 1];
		stack->next[uints[i]] = uints[(i + 1) % stack->size];
	}
	stack->fd = 1;
	stack->a = uints[0];
	stack->b = SIZE_MAX;
	stack->fseq = (unsigned char *)uints;
	stack->ranges[stack->ri].max = stack->size - 1;
	returnval = ps_main3(stack);
	free(uints);
	free(stack->prev);
	return (returnval < 0);
}

static size_t	str_to_uints(const char *str, size_t *uint, size_t y)
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

// program limit:
// your_ram - (SIZE_MAX/3 - this_struct - 11_output_strs_lens_fpointers).
// ngl it's useless but fun to stretch limits even though in theory no one has
// approximately 18446744073709551615/3 bytes of ram.
// For comparison a normal motherboard can 'only' carry:
// 128gb ram   = 128000000000 bytes.
////////////////////////////////////////////////////////////////////
//Notes:
//gotta love bash!        `./program arg1 arg2 arg3`
//is abs not the same as: `./program "arg1 arg2 arg3"`
int	main(int argc, char const **argv)
{
	t_stack			stack;
	int				i;
	size_t			*uints;

	if (argc < 2)
		return (ft_printf("Error\n"), EXIT_ERROR);
	ft_memset(&stack, 0, sizeof(t_stack));
	argv++;
	argc--;
	i = -1;
	while (++i < argc)
		stack.size += ft_countwords(argv[i], " \n\v\t\r");
	uints = (size_t *)malloc(stack.size * sizeof(size_t));
	if (!uints)
		return (EXIT_ERROR);
	i = -1;
	while (++i < argc)
	{
		stack.a = str_to_uints(argv[i], uints, stack.a);
		if (stack.a == 0)
			return (free(uints), ft_printf("Error\n"), EXIT_ERROR);
	}
	return (main2(uints, &stack));
}
