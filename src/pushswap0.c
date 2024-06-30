#include "pushswap.h"
#include "libft.h"

void	push_x_to_y(size_t *x, size_t *y, t_stack *s)
{
	size_t	temp;

	if (*x != SIZE_MAX)
	{
		s->prev[s->next[*x]] = s->prev[*x];
		s->next[s->prev[*x]] = s->next[*x];
		temp = *x;
		*x = s->next[*x];
		if (*x == temp)
			*x = SIZE_MAX;
		if (*y == SIZE_MAX)
		{
			*y = temp;
			s->next[*y] = temp;
			s->prev[*y] = temp;
		}
		else
		{
			s->next[temp] = *y;
			s->prev[temp] = s->prev[*y];
			s->prev[*y] = temp;
			s->next[s->prev[*y]] = temp;
			*y = temp;
		}
	}
}

void	swap(size_t *this, t_stack *s)
{
	size_t	temp[2];
	size_t	*next;
	size_t	*prev;

	next = s->next;
	prev = s->prev;
	if (next[*this] != *this)
	{
		temp[0] = *this;
		temp[1] = next[*this];
		prev[next[next[*this]]] = temp[0];
		next[temp[0]] = next[next[*this]];
		next[prev[*this]] = temp[1];
		prev[temp[1]] = prev[*this];
		prev[temp[0]] = temp[1];
		next[temp[1]] = temp[0];
		*this = prev[*this];
	}
}

//provide direction, reverse rotation = s->prev, normal rotation = s->next.
void	rotate(size_t *this, size_t *direction)
{
	if (*this != SIZE_MAX)
		*this = direction[*this];
}

void	rrr(t_stack *s)
{
	rotate(&s->a, s->prev);
	rotate(&s->b, s->next);
}
