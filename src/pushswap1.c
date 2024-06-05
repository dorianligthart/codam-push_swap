/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:19:11 by doligtha          #+#    #+#             */
/*   Updated: 2024/06/03 18:19:11 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdint.h>

int	pa(bool print, t_stack *s)
{
	push_x_to_y(&s->a, &s->b, s);
	return (write(1, "pa\n", 3 * print));
}

int	pb(bool print, t_stack *s)
{
    push_x_to_y(&s->b, &s->a, s);
	return (write(1, "pb\n", 3 * print));
}

int	sa(bool print, t_stack *s)
{
	swap(&s->a, s);
	return (write(1, "sa\n", 3 * print));
}

int	sb(bool print, t_stack *s)
{
	swap(&s->b, s);
	return (write(1, "sb\n", 3 * print));
}

int	ss(bool print, t_stack *s)
{
	swap(&s->a, s);
	swap(&s->b, s);
	return (write(1, "ss\n", 3 * print));
}
