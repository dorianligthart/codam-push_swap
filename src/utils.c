#include "pushswap.h"
#include "libft.h"

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

void	ps_printstack(size_t ptr, t_stack *stack)
{
	if (ptr == stack->a)
		ft_printf("%c[HEAD, ", 'A');
	else if (ptr == stack->b)
		ft_printf("%c[HEAD, ", 'B');
	else
		ft_printf("%c[HEAD, ", 'X');
	if (ptr != SIZE_MAX)
	{
		ft_printf("%u, ", (unsigned int)ptr);
		ptr = stack->next[ptr];
		while (ptr != stack->a && ptr != stack->b)
		{
			ft_printf("%u, ", (unsigned int)ptr);
			ptr = stack->next[ptr];
		}
	}
	else
		ft_printf("EMPTY, ");
	ft_printf("TAIL]\n");
}

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
