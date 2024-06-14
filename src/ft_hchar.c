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

