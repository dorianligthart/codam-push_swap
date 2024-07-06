/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:10:44 by doligtha          #+#    #+#             */
/*   Updated: 2024/07/06 17:30:44 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pushswap.h"
#include <stdarg.h>
#include <unistd.h>

//maybe will use this in future, needs debugging and i cant be bothered.
bool	ps_israngesorted(t_stack *s, size_t ptr, t_range *range, bool inverse)
{
	size_t	stay;
	size_t	n;

	if (ptr == SIZE_MAX)
		return (false);
	n = range->max - range->min + 1;
	stay = ptr;
	while (s->next[ptr] != stay && n--)
	{
		if (s->next[ptr] != ptr + (inverse == true) * -2 + 1)
			return (false);
		ptr = s->next[ptr];
	}
	return (true);
}

int	ps_write_fseq(t_stack *s)
{	
	unsigned char	right;
	unsigned char	left;
	size_t			iter;

	iter = 0;
	if (s->fseqlen == 0)
		return (EXIT_SUCCESS);
	while (iter <= s->fseqlen)
	{
		right = ft_hchar_getright(s->fseq[iter]);
		left = ft_hchar_getleft(s->fseq[iter]);
		if (write(s->fd, s->foutput[right], s->foutputlen[right]) < 0)
			return (EXIT_ERROR);
		if (left != F_NONE
			&& write(s->fd, s->foutput[left], s->foutputlen[left]) < 0)
			return (EXIT_ERROR);
		iter++;
	}
	return (EXIT_SUCCESS);
}

int	ps_write_fseq_in_chunks(t_stack *s)
{
	ssize_t			written;
	char			buffer[PS_WRITE_CHAR_COUNT];
	size_t			iter;
	unsigned char	right;
	unsigned char	left;

	iter = -1;
	written = 0;
	while (++iter < s->fseqlen + (s->fseq[s->fseqlen] != F_NONE)
			&& written >= 0 && written <= PS_WRITE_CHAR_COUNT - 8)
	{
		right = ft_hchar_getright(s->fseq[iter]);
		left = ft_hchar_getleft(s->fseq[iter]);
		// printf("%i --- %i\n", left, right);
		// printf("%zu --- %zu\n", iter, s->fseqlen);
		// printf("%s, %zu", s->foutput[right], s->foutputlen[right]);
		// printf("%s, %zu", s->foutput[left], s->foutputlen[left]);
		ft_memcpy(buffer + written, s->foutput[right], s->foutputlen[right]);
		written += s->foutputlen[right];
		if (left != F_NONE)
		{
			ft_memcpy(buffer + written, s->foutput[left], s->foutputlen[left]);
			written += s->foutputlen[left];
		}
		if (written >= PS_WRITE_CHAR_COUNT - 8
			|| iter == s->fseqlen + (s->fseq[s->fseqlen] != F_NONE))
			written = write(s->fd, buffer, written);
	}
	return (written >= 0);
}

void	ps_run(t_stack *s, unsigned char function)
{
	if (function == F_NONE || function >= F_COUNT)
		return ;
	s->fptrs[function](s);
	if (s->fseq[s->fseqlen] == F_NONE)
		s->fseq[s->fseqlen] = function;
	else
	{
		s->fseq[s->fseqlen] = ft_hchar_combine(
										s->fseq[s->fseqlen],
										function);
		s->fseqlen++;
	}
}

void	ps_run_multiple(t_stack *s, int count, ...)
{
	va_list	list;

	va_start(list, count);
	while (count--)
		ps_run(s, va_arg(list, int));
	va_end(list);
}
