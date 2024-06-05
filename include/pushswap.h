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
#  define PS_MAX_RANGE_SIZE 3
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
	RRA,
	RRB,
	RRR,
	PA,
	PB,
	RR,
	RB,
	RA,
	SA,
	SB,
	SS,
	END_AND_COUNT,
};

//todo: search for ss() oppertunities somehow!!

/*rangesize cases:
	2: check table,
	3: check table,
	4: check table,
	5: check table,
	6: split / 2 or 3, depending on result,
	7: split / 2 or 3, depending on result,
	8: split / 2 or 3, depending on result,
	9: 
*/

//sort stack B rangesize=3 to stack A:
//	B: [2, 1, 0 ...] -> pushB, pushB, pushB.
//	B: [2, 0, 1 ...] -> pushB, swapB, pushB, pushB.
//	B: [1, 2, 0 ...] -> swapB, pushB, pushB, pushB.
//	B: [0, 2, 1 ...] -> swapB, pushB, swapB, pushB, pushB.
//	B: [1, 0, 2 ...] -> revrotateB, swapB, pushB, rotateB, pushB, pushB.
//	B: [0, 1, 2 ...] -> revrotateB, swapB, pushB, pushB, rotateB, pushB.

//sort stack B rangesize=4 to stack A:
//	B:

// typedef struct s_range
// {
// 	size_t	min;
// 	size_t	max;
// 	size_t	size;
// 	size_t	move_count;
// }	t_range;

// typedef struct s_ranges
// {
// 	t_range	*range;
// 	size_t	count;
// 	size_t	mod;
// }	t_ranges;

typedef struct s_stack
{
	size_t			*prev;
	size_t			*next;
	size_t			size;
	size_t			a;
	size_t			b;
	size_t			move_count;
	int				fd;
	unsigned char	*fseq;
	size_t			fseqiterate;
	size_t			fseqlen;
	int				(*functionpointers)(bool, t_stack *);
}	t_stack;

void	ps_printstack(size_t ptr, t_stack *stack);
bool	ps_algorithm_init(t_stack *stack);

//push stack x 'node' on top of stack y 'node' :
void	push_x_to_y(size_t *x, size_t *y, t_stack *s);

//swap stack this with s->next[this] :
void	swap(size_t *this, t_stack *s);

//rotate stack this in dir direction
void	rotate(size_t *this, size_t *direction);

//function pointers :

int	pa(bool print, t_stack *s);
int	pb(bool print, t_stack *s);
int	sa(bool print, t_stack *s);
int	sb(bool print, t_stack *s);
int	ss(bool print, t_stack *s);
int	ra(bool print, t_stack *s);
int	rb(bool print, t_stack *s);
int	rr(bool print, t_stack *s);
int	rra(bool print, t_stack *s);
int	rrb(bool print, t_stack *s);
int	rrr(bool print, t_stack *s);
#endif

//project description: 
// pa (push a):
//		Take the first element at the top of b and put it at the top of a.
//		Do nothing if b is empty.
// pb (push b):
//		Take the first element at the top of a and put it at the top of b.
//		Do nothing if a is empty.
// sa (swap a):
//		Swap the first 2 elements at the top of stack a.
// 		Do nothing if there is only one or no elements.
// sb (swap b):
//		Swap the first 2 elements at the top of stack b.
// 		Do nothing if there is only one or no elements.
// ss : swap a and b at the same time. see sa() and sb();
// ra (rotate a):
//		Shift up all elements of stack a by 1.
//		The first element becomes the last one.
// rb (rotate b):
//		Shift up all elements of stack b by 1.
//		The first element becomes the last one.
// rr:	Rotate a and b.
// rra (reverse rotate a):
//		Shift down all elements of stack a by 1.
//		The last element becomes the first one.
// rrb (reverse rotate b):
//		Shift down all elements of stack b by 1.
//		The last element becomes the first one.
// rrr:	Reverse Rotate a and b.#endif //PUSHSWAP_H