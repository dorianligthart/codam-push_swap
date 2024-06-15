/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:25:38 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/21 10:25:38 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdarg.h> //va_list, va_start(), va_arg(), va_end()
#include <unistd.h> //write()
#include <stdlib.h>
#include <stdint.h>

//NEW LIBFT FUNCTIONS :

//loops through stack, finds the smallest && bigger than index and set to index.
//messes up data if there are duplicates.
void	ft_normalise_size(size_t *dst, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	min;
	size_t	tmp;

	tmp = 0;
	y = 0;
	while (y < size)
	{
		x = 0;
		min = SIZE_MAX;
		while (x < size)
		{
			if ((min > dst[x]
				|| (y == size - 1 && dst[x] == SIZE_MAX))
				&& y <= dst[x])
			{
				min = dst[x];
				tmp = x;
			}
			x++;
		}
		dst[tmp] = y;
		y++;
	}
}

char	*ft_strchr(const char *s, int c);
//" \n\v\t\r"
//Like unix's: `tr 'delims' '\n' | wc -l`
size_t	ft_countwords(const char *str, const char *delims)
{
	size_t		wordcount;
	size_t		i;
	size_t		strlen;

	wordcount = 0;
	strlen = 0;
	while (str[strlen])
		strlen++;
	i = 0;
	while (i < strlen)
	{
		while (ft_strchr(delims, str[i]) != NULL)
			i++;
		wordcount++;
		while (ft_strchr(delims, str[i]) == NULL)
			i++;
	}
	return (wordcount);
}

//OLDER FUNCTIONS :

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
        if (dest && !src)
                return (dest);
        if (!dest || !src)
                return (NULL);
        while (n--)
                *(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
        return (dest);
}

void    *ft_memset(void *s, int c, size_t n)
{
        size_t  i;

        i = 0;
        while (s && n--)
                ((unsigned char *)s)[i++] = (unsigned char)c;
        return (s);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = -1;
	while (s && s[++i])
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
	if (s && (unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (*nptr == '-' || *nptr == '+')
		i++;
	while (result <= INT_MAX / 10 && nptr[i] >= '0' && nptr[i] <= '9')
		result = (result * 10) + (nptr[i++] - '0');
	if (nptr[0] == '-')
		result *= -1;
	return (result);
}

static int	puint(int fd, unsigned long nbr, char *basestr)
{
	unsigned long	divider;
	int				base;
	int				i;
	char			put[31];

	base = 0;
	while (basestr && basestr[base])
		base++;
	if (base < 2)
		return (-1);
	divider = 1;
	while (divider <= nbr / base)
		divider = divider * base;
	i = 0;
	while (divider)
	{
		put[i] = basestr[nbr / divider];
		nbr = nbr % divider;
		divider = divider / base;
		i++;
	}
	put[i] = '\0';
	return (write(fd, put, i));
}

static int	newformat2(int fd, const char **format, va_list *list, int tmp)
{
	int	nbr;

	if (*(*format - 1) == 'p')
	{
		nbr = va_arg(*list, unsigned long);
		if (!nbr)
			return (write(fd, "(nil)", 5));
		tmp = write(fd, "0x", 2);
		nbr = puint(fd, nbr, "0123456789abcdef");
		return (-1 + (tmp >= 0 && nbr >= 0) * (tmp + nbr + 1));
	}
	else if ((*(*format - 1) == 'd' || *(*format - 1) == 'i'))
	{
		nbr = va_arg(*list, int);
		if (nbr == -2147483648)
			return (write(fd, "-2147483648", 11));
		if (nbr < 0)
		{
			tmp = write(fd, "-", 1);
			nbr *= -1;
		}
		nbr = puint(fd, nbr, "0123456789");
		return (-1 + (tmp >= 0 && nbr >= 0) * (tmp + nbr + 1));
	}
	return (puint(fd, va_arg(*list, unsigned int), "0123456789"));
}

static int	newformat(int fd, const char **format, va_list *list, int tmp)
{
	char	*s;

	if (!ft_strchr("cspdiuxX%", **format))
		return (0);
	if (*(++*format) == '%')
		return (write(fd, "%", 1));
	else if (*(*format - 1) == 'c')
	{
		tmp = va_arg(*list, int);
		return (write(fd, &tmp, 1));
	}
	else if (*(*format - 1) == 's')
	{
		s = va_arg(*list, char *);
		if (!s)
			return (write(fd, "(null)", 6));
		while (s[tmp])
			tmp++;
		return (write(fd, s, tmp));
	}
	else if (*(*format - 1) == 'x')
		return (puint(fd, va_arg(*list, unsigned int), "0123456789abcdef"));
	else if (*(*format - 1) == 'X')
		return (puint(fd, va_arg(*list, unsigned int), "0123456789ABCDEF"));
	return (newformat2(fd, format, list, 0));
}

int	ft_printf(const char *format, ...)
{
	va_list		list;
	int			printed;
	int			x;
	int			y;
	const char	*tmp;

	if (!format)
		return (-1);
	va_start(list, format);
	printed = 0;
	while (*format)
	{
		tmp = format;
		while (*format && *format != '%')
			format++;
		x = write(1, tmp, format - tmp);
		y = 0;
		if (*format == '%' && format++)
			y = newformat(1, &format, &list, 0);
		if (y < 0 || x < 0)
			return (-1);
		printed = printed + x + y;
	}
	va_end(list);
	return (printed);
}
