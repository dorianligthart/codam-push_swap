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

// push_swap note:
// usual stack sizes * sizeof(size_t) * sizeof(char) * 2;
// 100*8*1*2 = 1600functionslots.
// 500*8*1*2 = 8000functionslots.
// 
// as much as I would like (argc / movecount) to be linear, it isn't.
// so we must find a way to compress even further or handle it by chunks....
// but that is for another project!
///////////////////////////////////////

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
