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

//	funfact: we only need at most 64 ranges! even with SIZE_MAX digits.
//	because 2^64 is (SIZE_MAX - 1). and we only support (your ram - SIZE_MAX/3 - some kb)
//	we also use consecutive even/odd ranges on the smallest range size ranges.
# ifndef PS_RANGE_COUNT
#  define PS_RANGE_COUNT 64
# endif

# ifndef PS_WRITE_CHAR_COUNT
#  define PS_WRITE_CHAR_COUNT 64
# endif

# ifndef EXIT_ERROR
#  define EXIT_ERROR 1
# endif

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h> //SIZE_MAX

//function ptr struct;
enum e_functions
{
	F_NONE,
	F_PA,
	F_RA,
	F_RB,
	F_RR,
	F_SA,
	F_SB,
	F_SS,
	F_NONE2,
	F_PB,
	F_RRA,
	F_RRB,
	F_RRR,
	FU_SA,
	FU_SB,
	FU_SS,
	F_COUNT,
};

typedef struct s_range
{
	size_t	min;
	size_t	max;
}	t_range;

typedef struct s_stack
{
	size_t			size;
	size_t			*prev;
	size_t			*next;
	size_t			a;
	size_t			b;
	t_range			ranges[PS_RANGE_COUNT];
	unsigned char	ri;
	bool			ranges_is_odd[PS_RANGE_COUNT];
	bool			ranges_is_even[PS_RANGE_COUNT];
	unsigned char	*fseq;
	size_t			fseqlen;
	int				fd;
	void			(**fptrs)(struct s_stack *);
	const char		**foutput;
	const size_t	*foutputlen;
	unsigned char	a_bot_count;
	unsigned char	b_bot_count;
}	t_stack;

//debug :

void	ps_printrange(t_stack *s, unsigned char howmany);
void	ps_printstack(t_stack *s, size_t ptr);
void	ps_printprevnext(t_stack *s);

//function sequence :

void	ps_run(t_stack *s, unsigned char function);
void	ps_run_multiple(t_stack *s, int count, ...);
void	ps_undo_multiple(t_stack *s, size_t amount);
int		ps_write_fseq(t_stack *s);

//algorithm :

void	ps_algorithm_entry(t_stack *s);
void	ps_split_range_a_into_3(t_stack *s, t_range *lower,
								t_range *middle, t_range *higher);
void	ps_split_range_a(t_stack *s, t_range *lower, t_range *higher);
void	ps_split_range_b(t_stack *s, t_range *lower, t_range *higher);

//hchar functions :

unsigned char	ft_hchar_combine(unsigned char left, unsigned char right);
unsigned char	ft_hchar_getleft(unsigned char lefrig);
unsigned char	ft_hchar_getright(unsigned char lefrig);

//double array linked circular list manipulation (pushswap0-3.c) :

//push stack x 'node' on top of stack y 'node' :
void	push_x_to_y(size_t *x, size_t *y, t_stack *s);

//swap this with s->next[this] :
void	swap(size_t *this, t_stack *s);

//rotate *this in prev or next direction
void	rotate(size_t *this, size_t *direction);

void	pa(t_stack *s);
void	pb(t_stack *s);
void	sa(t_stack *s);
void	sb(t_stack *s);
void	ss(t_stack *s);
void	ra(t_stack *s);
void	rb(t_stack *s);
void	rr(t_stack *s);
void	rra(t_stack *s);
void	rrb(t_stack *s);
void	rrr(t_stack *s);

#endif //PUSHSWAP_H

//SHORT project description:
//	You start with 2 stacks, stack A and stack B.
//	Stack A is full of unordered integers, stack B is empty.
//	Order the digits using the least amount of the following moves:  
//		pa (push a):	Take the first element at the top of b and put
//						it at the top of a. Do nothing if b is empty.
//		pb (push b):	Take the first element at the top of a and put
//						it at the top of b. Do nothing if a is empty.
//		sa (swap a):	Swap the first 2 elements at the top of stack a.
//						Do nothing if there is only one or no elements.
//		sb (swap b):	Swap the first 2 elements at the top of stack b.
//						Do nothing if there is only one or no elements. 
//		ss (sa + sb):	swap stack a and b's 1st and 2nd element.
//		ra (backward a):	Shift up all elements of stack a by 1. 
//							The first element becomes the last one.
//		rb (backward b):	Shift up all elements of stack b by 1. 
//							The first element becomes the last one.
//		rr (backward ab):	Shift up all elements of stack a and b by 1.
//		rra (forward a):	Shift down all elements of stack a by 1.
//							The last element becomes the first one.
//		rrb (forward b):	Shift down all elements of stack b by 1.
//							The last element becomes the first one.
//		rrr (forward ab):	Shift down all elements of stack a and b by 1.


// push_swap note:
// usual stack sizes * sizeof(size_t) * sizeof(char) * 2;
// 100*8*1*2 = 1600functionslots.
// 500*8*1*2 = 8000functionslots.
// 
// as much as I would like (argc / movecount) to be linear, it isn't.
// so we must find a way to compress even further or handle it by chunks....
// but that is for another project!
///////////////////////////////////////

