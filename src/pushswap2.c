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

void	ra(t_stack *s)
{
	rotate(&s->a, s->next);
}

void	rb(t_stack *s)
{
	rotate(&s->b, s->next);
}

void	rr(t_stack *s)
{
	rotate(&s->a, s->next);
	rotate(&s->b, s->next);
}

void	rra(t_stack *s)
{
	rotate(&s->a, s->prev);
}

void	rrb(t_stack *s)
{
	rotate(&s->b, s->prev);
}
