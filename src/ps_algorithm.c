/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_algorithm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:47:45 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 03:29:23 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdint.h>

void	ps_printstacks(t_dcllist *s, size_t a, size_t b)
{
	size_t ptr;

	ft_printf("A_HEAD = %u\n", a);
	ptr = a;
	while (s->next[ptr] != a)
	{
		ft_printf("\n[");
		ft_printf("%u\t", ptr);
		ft_printf("%u\t", s->next[ptr]);
		ft_printf("%u\t", s->prev[ptr]);
		ft_printf("]\n");
		ptr = s->next[ptr];
	}
	ft_printf("B_HEAD = %u\n", b);
	ptr = b;
	while (s->next[ptr] != a)
	{
		ft_printf("\n[");
		ft_printf("%u\t", ptr);
		ft_printf("%u\t", s->next[ptr]);
		ft_printf("%u\t", s->prev[ptr]);
		ft_printf("]\n");
		ptr = s->next[ptr];
	}
}

//some value setting function;
//	- b initialised as SIZE_MAX meaning it's empty;
bool	ps_algorithm(t_dcllist *s, size_t a)
{
	ps_pa(s);
	ps_printstacks(s, a, SIZE_MAX);
	return (true);
}
