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

// i = (i < PS_WRITE_BUF_SIZE - 8 && write(s->fd, buffer, i)) * i;
//I wish I could assert PS_WRITE_BUF_SIZE here!!
bool	ps_write_fseq(t_stack *s)
{
	char			buffer[PS_WRITE_BUF_SIZE];
	int				i;
	size_t			iter;
	unsigned char	right;
	unsigned char	left;

	if (PS_WRITE_BUF_SIZE < 8)
		return (false);
	iter = 0;
	i = 0;
	while (iter < s->fseqlen)
	{
		right = ft_hchar_getright(s->fseq[iter]);
		ft_memcpy(buffer, s->foutput[right], s->foutputlen[right]);
		left = ft_hchar_getleft(s->fseq[iter]);
		ft_memcpy(buffer, s->foutput[left], s->foutputlen[left]);
		if (i < PS_WRITE_BUF_SIZE - 8 && write(s->fd, buffer, i) < 0)
			return (false);
		i += s->foutputlen[right] + s->foutputlen[left];
	}
	return (true);
}

static int	ps_initialise2(t_stack *stack)
{
	void		(*fptrs[F_COUNT])(t_stack *) = {[F_PA] = pa,
					[F_RA] = ra, [F_RB] = rb, [F_RR] = rr,
					[F_SA] = sa, [F_SB] = sb, [F_SS] = ss, [F_PB] = pb, 
					[F_RRA] = rra, [F_RRB] = rrb, [F_RRR] = rrr,
					[FU_SA] = sa, [FU_SB] = sb, [FU_SS] = ss};
	const char	*foutput[F_COUNT] = {[F_PA] = "pa\n", [F_RA] = "ra\n",
					[F_RB] = "rb\n", [F_RR] = "rr\n", [F_SA] = "sa\n",
					[F_SB] = "sb\n", [F_SS] = "ss\n", [F_PB] = "pb\n",
					[F_RRA] = "rra\n", [F_RRB] = "rrb\n", [F_RRR] = "rrr\n",
					[FU_SA] = "sa\n", [FU_SB] = "sb\n", [FU_SS] = "ss\n"};
	const int	foutputlen[F_COUNT] = {[F_PA] = 3, [F_RA] = 3, [F_RB] = 3,
					[F_RR] = 3, [F_SA] = 3, [F_SB] = 3, [F_SS] = 3,
					[F_PB] = 3, [F_RRA] = 4, [F_RRB] = 4,
					[F_RRR] = 4,[FU_SA] = 3, [FU_SB] = 3, [FU_SS] = 3};

	stack->next = stack->prev + stack->size;
	stack->b = SIZE_MAX;
	stack->fseqlen = 0;
	stack->fptrs = fptrs;
	stack->foutput = foutput;
	stack->foutputlen = foutputlen;
	ps_algorithm_entry(stack);
	free(stack->prev);
	free(stack->fseq);
	return (EXIT_SUCCESS);
}

static int	ps_initialise(unsigned int *uints, t_stack *stack)
{
	size_t	*array;
	size_t	i;

	stack->fd = 1;
	array = (size_t *)malloc(stack->size * sizeof(size_t));
	if (array == NULL)
		return (free(uints), EXIT_ERROR);
	i = -1;
	while (++i < stack->size)
		array[i] = (size_t)uints[i];
	free(uints);
	ft_normalise_size(array, stack->size);
	stack->prev = (size_t *)malloc((2 * stack->size) * sizeof(size_t));
	if (stack->prev == NULL)
		return (free(array), EXIT_ERROR);
	stack->next = stack->prev + stack->size;
	i = -1;
	while (++i < stack->size)
	{
		stack->prev[array[i]] = array[i + (i == 0) * stack->size - 1];
		stack->next[array[i]] = array[(i + 1) % stack->size];
	}
	stack->a = array[0];
	stack->fseq = (unsigned char *)array;
	return (ps_initialise2(stack));
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
	unsigned int	*uints;

	if (argc < 2)
		return (ft_printf("Error.\n"), EXIT_ERROR);
	ft_memset(stack.ranges, 0, sizeof(t_range) * PS_RANGE_COUNT);
	argv++;
	argc--;
	stack.size = 0;
	i = -1;
	while (++i < argc)
		stack.size += ft_countwords(argv[i], " \n\v\t\r");
	uints = (unsigned int *)malloc(stack.size * sizeof(unsigned int));
	if (!uints)
		return (EXIT_ERROR);
	stack.a = 0;
	i = -1;
	while (++i < argc)
	{
		stack.a = str_to_uints(argv[i], uints, stack.a);
		if (stack.a == 0)
			return (free(uints), EXIT_ERROR);
	}
	return (ps_initialise(uints, &stack));
}
