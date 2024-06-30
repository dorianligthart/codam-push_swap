/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:10:44 by doligtha          #+#    #+#             */
/*   Updated: 2024/06/15 08:04:27 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include <stdarg.h>
#include <unistd.h>

void	ps_run(t_stack *s, unsigned char function)
{
	if (function == F_NONE || function >= F_COUNT)
		return ;
	if (s->fseq[s->fseqlen] == F_NONE)
		s->fseq[s->fseqlen] = function;
	else
	{
		s->fseq[s->fseqlen] = ft_hchar_combine(
										s->fseq[s->fseqlen],
										function);
		s->fseqlen++;
	}
	s->fptrs[function](s);
}

void	ps_run_multiple(t_stack *s, int count, ...)
{
	va_list	list;

	va_start(list, count);
	while (count--)
		ps_run(s, va_arg(list, int));
	va_end(list);
}
