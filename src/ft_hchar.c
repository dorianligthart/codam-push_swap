/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 05:38:44 by doligtha          #+#    #+#             */
/*   Updated: 2024/06/13 05:38:44 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"

//this file is dedicated to storing and getting 4bit integers.
//by using half of an unsigned char.

unsigned char	ft_hchar_combine(unsigned char left, unsigned char right)
{
	return ((left << 4) | right);
}

unsigned char	ft_hchar_getleft(unsigned char lefrig)
{
	return (lefrig >> 4);
}

unsigned char	ft_hchar_getright(unsigned char lefrig)
{
	return (lefrig & 0x0F);
}

int	ps_write_fseq(t_stack *s)
{
	ssize_t			written;
	char			buffer[PS_WRITE_BUF_SIZE];
	size_t			iter;
	unsigned char	right;
	unsigned char	left;

	iter = -1;
	written = 0;
	while (++iter < s->fseqlen + (s->fseq[s->fseqlen] != F_NONE)
			&& written >= 0 && written <= PS_WRITE_BUF_SIZE - 8)
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
		if (written >= PS_WRITE_BUF_SIZE - 8
			|| iter == s->fseqlen + (s->fseq[s->fseqlen] != F_NONE))
			written = write(s->fd, buffer, written);
	}
	return (written >= 0);
}
