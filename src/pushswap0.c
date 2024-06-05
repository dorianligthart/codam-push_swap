#include "pushswap.h"
#include "libft.h"
#include <stdio.h>

void print_example(void)
{
    unsigned char a = 9; // Example value for the first 4-bit integer (1001 in binary)
    unsigned char b = 6; // Example value for the second 4-bit integer (0110 in binary)

    // Combine the two 4-bit integers into a single char
    unsigned char combined = (a << 4) | b;

    // Extract the higher 4-bit integer
    unsigned char extracted_a = combined >> 4;

    // Extract the lower 4-bit integer
    unsigned char extracted_b = combined & 0x0F;

    printf("Original a: %u\n", a);
    printf("Original b: %u\n", b);
    printf("Combined: %u\n", combined);
    printf("Extracted a: %u\n", extracted_a);
    printf("Extracted b: %u\n", extracted_b);
}

// //not really the actual cost but a good indicator;
// size_t	ps_getcost(size_t *prev, size_t *next, t_stack *stack)
// {
// 	size_t	cost;
// 	size_t	ui;

// 	(void)prev;
// 	(void)stack;
// 	cost = 0;
// 	ui = 0;
// 	while (next[ui])
// 	{
// 		if (cost < SIZE_MAX - ui)
// 		{
// 			if (ui >= next[ui])
// 				cost += (ui - next[ui]) * 2;
// 			else
// 				cost += (next[ui] - ui) * 2;
// 		}
// 	}
// 	return (cost);
// }

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

int	rrr(bool print, t_stack *s)
{
	rotate(&s->a, s->prev);
	rotate(&s->b, s->prev);
	return (write(1, "rrr\n", 4 * print));
}
