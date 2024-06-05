/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:18:51 by doligtha          #+#    #+#             */
/*   Updated: 2024/06/03 18:18:51 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdint.h>

int	ra(bool print, t_stack *s)
{
	rotate(&s->a, s->next);
	return (write(1, "ra\n", 3 * print));
}

int	rb(bool print, t_stack *s)
{
	rotate(&s->b, s->next);
	return (write(1, "rb\n", 3 * print));
}

int	rr(bool print, t_stack *s)
{
	rotate(&s->a, s->next);
	rotate(&s->b, s->next);
	return (write(1, "rr\n", 3 * print));
}

int	rra(bool print, t_stack *s)
{
	rotate(&s->a, s->prev);
	return (write(1, "rra\n", 4 * print));
}

int	rrb(bool print, t_stack *s)
{
	rotate(&s->b, s->prev);
	return (write(1, "rrb\n", 4 * print));
}
