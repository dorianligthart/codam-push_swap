#include "pushswap.h"
#include "libft.h"

void	push_x_to_y(size_t *x, size_t *y, t_stack *s)
{
	size_t	temp;

	if (*x != SIZE_MAX)
	{
		temp = *x;
		s->prev[s->next[*x]] = s->prev[*x];
		s->next[s->prev[*x]] = s->next[*x];
		*x = s->next[*x];
		if (*x == temp)
			*x = SIZE_MAX;
		if (*y == SIZE_MAX)
			*y = temp;
		else
		{
			s->next[temp] = *y;
			s->prev[temp] = *y;
			s->next[*y] = temp;
			s->prev[*y] = temp;
		}
	}
}

void	swap(size_t *this, t_stack *s)
{
	size_t	t[2];
	size_t	*next;
	size_t	*prev;

	next = s->next;
	prev = s->prev;
	if (next[*this] != *this)
	{
		(t[0] = *this, t[1] = next[*this]);
		prev[next[next[*this]]] = t[0];
		next[t[0]] = next[next[*this]];
		next[prev[*this]] = t[1];
		prev[t[1]] = prev[*this];
		prev[t[0]] = t[1];
		next[t[1]] = t[0];
		*this = prev[*this];
	}
}

//provide direction, reverse = s->prev, normal = s->next.
void	rotate(size_t *this, size_t *direction)
{
	if (*this != SIZE_MAX && direction[*this] != *this)
		*this = direction[*this];
}

void	rrr(t_stack *s)
{
	rotate(&s->a, s->prev);
	rotate(&s->b, s->prev);
}
