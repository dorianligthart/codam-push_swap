/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_sequence.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:11:49 by doligtha          #+#    #+#             */
/*   Updated: 2024/06/08 21:11:49 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"
#include "libft.h"
#include <stdlib.h>

//runs specified function, adds 4bits to char array identifying which function.
//sizeof(size_t) = 8; 64bits; so 64 / 4 = 16functions.
//100*16 = 1600functionslots.
//500*16 = 8000functionslots.
//as much as I would like intcount/movecount to be linear, it sadly isn't.
//so we must find a way to compress even further.
//but that is for another project. for now we let return 1.
void	ps_run(t_stack *s, unsigned char function)
{
	if (function == F_NONE || function >= F_COUNT)
		return ;
	(void)s;
}

//optimises moves, moves iterator, and outputs move to s->fd.
bool	ps_displaymoves(t_stack *s)
{
	(void)s;
	free(s->fseq);
	return (true);
}
