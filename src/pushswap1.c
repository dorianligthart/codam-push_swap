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

void	pa(t_stack *s)
{
	push_x_to_y(&s->b, &s->a, s);
}

void	pb(t_stack *s)
{
    push_x_to_y(&s->a, &s->b, s);
}

void	sa(t_stack *s)
{
	swap(&s->a, s);
}

void	sb(t_stack *s)
{
	swap(&s->b, s);
}

void	ss(t_stack *s)
{
	swap(&s->a, s);
	swap(&s->b, s);
}
