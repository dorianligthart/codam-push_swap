#include "pushswap.h"
#include "libft.h"

void	ps_printprevnext(t_stack *s)
{
	size_t i;

	ft_printf("A=%u, B=%u\n", s->a, s->b);
	write(1, "prev[", 5);
	i = -1;
	while (++i < s->size)
		ft_printf("%u, ", s->prev[i]);
	write(1, "]\nnext[", 7);
	i = -1;
	while (++i < s->size)
		ft_printf("%u, ", s->next[i]);
	write(1, "]\n\n", 3);
}

//you may ask why not use int, but it's for readability.
//there are at most 64 ranges. 
void	ps_printrange(t_stack *s, unsigned char howmany)
{
	unsigned char	i;

	i = 0;
	while (i < howmany && i <= s->ri)
	{
		ft_printf("ranges[%u]: {min=%u, max=%u}\n", s->ri - i,
				  s->ranges[s->ri - i].min, s->ranges[s->ri - i].max);
		i++;
	}

}

void	ps_printstack(t_stack *s, size_t ptr)
{
	if (ptr == s->a)
		ft_printf("%c[", 'A');
	else if (ptr == s->b)
		ft_printf("%c[", 'B');
	else
		ft_printf("%c[", 'X');
	if (ptr != SIZE_MAX)
	{
		ft_printf("%u, ", (unsigned int)ptr);
		ptr = s->next[ptr];
		while (ptr != s->a && ptr != s->b)
		{
			ft_printf("%u, ", (unsigned int)ptr);
			ptr = s->next[ptr];
		}
	}
	else
		ft_printf("EMPTY");
	ft_printf("]\n");
}
