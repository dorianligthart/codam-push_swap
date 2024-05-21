#include <limits.h>
#include <stdarg.h> //va_list, va_start(), va_arg(), va_end()
#include <unistd.h> //write()
#include <stdlib.h>

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

//" \n\v\t\r"
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

void	ft_free(void **address)
{
	int	i;

	i = 0;
	while (address[i] != NULL)
	{
		free(address[i]);
		i++;
	}
	free(address);
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

static char	**it(const char *s, char c, int w, int i)
{
	char	**s2;
	int		words;

	words = 0;
	while (s && s[i])
		if (s[i++] != c && (s[i] == c || s[i] == '\0'))
			words++;
	s2 = (char **)malloc((words + 1) * sizeof(char *));
	s2[words] = NULL;
	while (s2 && i--)
	{
		if (s[i] != c && ++w && (i == 0 || s[i - 1] == c))
		{
			s2[--words] = (char *)malloc((w + 1) * sizeof(char));
			if (!s2[words])
			{
				while (s2[++words])
					free(s2[words]);
				return (free(s2), NULL);
			}
			s2[words][w++] = '\0';
			while (--w)
				s2[words][w - 1] = s[i + w - 1];
		}
	}
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	return (it(s, c, 0, 0));
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
