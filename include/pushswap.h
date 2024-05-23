/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:22 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/16 18:07:34 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# ifndef PS_MAX_RANGE_SIZE
#  define PS_MAX_RANGE_SIZE 8
# endif

# ifndef PS_ERROR
#  define PS_ERROR 1
# endif

# ifndef PS_SUCCESS
#  define PS_SUCCESS 0
# endif

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h> //SIZE_MAX

//function ptr struct;
enum e_functions
{
	END,
	PA,
	PB,
	SA,
	SB,
	SS,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	FUNCTIONS,
};

typedef struct s_ranges
{
	t_range	*range;
	size_t		size;
}	t_ranges;


typedef struct s_range
{
	size_t	min;
	size_t	max;
	size_t	size;
	size_t	move_count;
}	t_range;

typedef struct s_stack
{
	size_t			size;
	size_t			a;
	size_t			b;
	size_t			move_count;
	bool			print;
	int				fd;
	unsigned char	*funcseq;
	size_t			funclen;
}	t_stack;

void	printstack(size_t *next, t_stack *stack, size_t ptr);
bool	algorithm(size_t *prev, size_t *next, t_stack *stack);

// pa (push a):
//		Take the first element at the top of b and put it at the top of a.
//		Do nothing if b is empty.
bool	pa(size_t *prev, size_t *next, t_stack *stack);

// pb (push b):
//		Take the first element at the top of a and put it at the top of b.
//		Do nothing if a is empty.
bool	pb(size_t *prev, size_t *next, t_stack *stack);

// sa (swap a):
//		Swap the first 2 elements at the top of stack a.
// 		Do nothing if there is only one or no elements.
bool	sa(size_t *prev, size_t *next, t_stack *stack);

// sb (swap b):
//		Swap the first 2 elements at the top of stack b.
// 		Do nothing if there is only one or no elements.
bool	sb(size_t *prev, size_t *next, t_stack *stack);

// ss : swap a and b at the same time. see sa() and sb();
bool	ss(size_t *prev, size_t *next, t_stack *stack);

// ra (rotate a):
//		Shift up all elements of stack a by 1.
//		The first element becomes the last one.
bool	ra(size_t *prev, size_t *next, t_stack *stack);

// rb (rotate b):
//		Shift up all elements of stack b by 1.
//		The first element becomes the last one.
bool	rb(size_t *prev, size_t *next, t_stack *stack);

// rr:	Rotate a and b.
bool	rr(size_t *prev, size_t *next, t_stack *stack);

// rra (reverse rotate a):
//		Shift down all elements of stack a by 1.
//		The last element becomes the first one.
bool	rra(size_t *prev, size_t *next, t_stack *stack);

// rrb (reverse rotate b):
//		Shift down all elements of stack b by 1.
//		The last element becomes the first one.
bool	rrb(size_t *prev, size_t *next, t_stack *stack);

// rrr:	Reverse Rotate a and b.
bool	rrr(size_t *prev, size_t *next, t_stack *stack);
#endif //PUSHSWAP_H

