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

//funfact: we only need at most 60 ranges!
# ifndef PS_RANGE_COUNT
#  define PS_RANGE_COUNT 64
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

/*Hard coded stacksize cases:
	2: solve3(A),
	3: solve3(A),
	4: TODO: make function to hardcode size 4,
	5: split / 2, A:3, B:2;		solve3(A), solve3(B), pushB, pushB.
	6: split / 2, A:3, B:3;		solve3(A), solve3(B), pushB, pushB, pushB.
	7: split / 3, A:3, B:2,2;	solve3(A), pushB, pushB, (swapAB), pushB, pushB.
	8: split / 3, A:3, B:2,3;	solve3(A), pushB, pushB, (swapA), solve3(B), pushB, pushB, pushB.
	9: split / 3, A:3, B:3,3;	solve3(A), pushB, pushB, pushB, solve3notempty(B),
								pushB, pushB, pushB, solve3(B), pushB, pushB, pushB.
	x > 9, use general algorithm....

Non empty stack rangesize cases:
rangesize=2 on stack A:
	A: [0, 1 ...] -> .
	A: [1, 0 ...] -> swapA.

rangesize=2 on stack B:
	B: [1, 0 ...] -> pushB, pushB.
	B: [0, 1 ...] -> swapB, pushB, pushB.

rangesize=3 on stack A:
	A: [0, 1, 2 ...] -> .
	A: [1, 0, 2 ...] -> swapA.
	A: [0, 2, 1 ...] -> rotA, swapA, revrotA.
	A: [1, 2, 0 ...] -> rotA, swapA, revrotA, swapA.
	A: [2, 0, 1 ...] -> swapA, rotA, swapA, revrotA.
	A: [2, 1, 0 ...] -> swapA, rotA, swapA, revrotA, swapA.

rangesize=3 on stack B:
	B: [2, 1, 0 ...] -> pushB, pushB, pushB.
	B: [2, 0, 1 ...] -> pushB, swapB, pushB, pushB.
	B: [1, 2, 0 ...] -> swapB, pushB, pushB, pushB.
	B: [0, 2, 1 ...] -> swapB, pushB, swapB, pushB, pushB.
	B: [1, 0, 2 ...] -> revrotB, swapB, pushB, rotB, pushB, pushB.
	B: [0, 1, 2 ...] -> revrotB, swapB, pushB, pushB, rotB, pushB.

rangesize=4 on stack A:
	A: [0, 1, 2, 3 ...] -> .
	A: [1, 0, 2, 3 ...] -> swapA.
	A: [0, 2, 1, 3 ...] -> rotA, swapA, revrotA.
	A: [1, 2, 0, 3 ...] -> rotA, swapA, revrotA, swapA.
	A: [2, 0, 1, 3 ...] -> swapA, rotA, swapA, revrotA.
	A: [2, 1, 0, 3 ...] -> swapA, rotA, swapA, revrotA, swapA.
	A: [0, 1, 3, 2 ...] -> rotA, rotA, swapA, revrotA, revrotA.
	A: [1, 0, 3, 2 ...] -> rotA, rotA, swapA, revrotA, revrotA, swapA.
	A: [0, 2, 3, 1 ...] -> rotA, rotA, swapA, revrotA, swapA, revrotA.
	A: [1, 2, 3, 0 ...] -> rotA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [2, 0, 3, 1 ...] -> swapA, rotA, rotA, swapA, revrotA, swapA, revrotA.
	A: [2, 1, 3, 0 ...] -> swapA, rotA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [0, 3, 1, 2 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA.
	A: [1, 3, 0, 2 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA, swapA.
	A: [0, 3, 2, 1 ...] -> rotA, swapA, rotA, swapA, revrotA, swapA, revrotA.
	A: [1, 3, 2, 0 ...] -> rotA, swapA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [2, 3, 0, 1 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA.
	A: [2, 3, 1, 0 ...] -> rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA, swapA.
	A: [3, 0, 1, 2 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA.
	A: [3, 1, 0, 2 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA, swapA.
	A: [3, 0, 2, 1 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, swapA, revrotA.
	A: [3, 1, 2, 0 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, swapA, revrotA, swapA.
	A: [3, 2, 0, 1 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA.
	A: [3, 2, 1, 0 ...] -> swapA, rotA, swapA, rotA, swapA, revrotA, revrotA, swapA, rotA, swapA, revrotA, swapA.

rangesize=4 to stack A:
	B: [3, 2, 1, 0 ...] -> pushB, pushB, pushB, pushB.
	B: [3, 2, 0, 1 ...] -> pushB, pushB, swapB, pushB, pushB.
	B: [3, 1, 2, 0 ...] -> pushB, swapB, pushB, pushB, pushB.
	B: [3, 0, 2, 1 ...] -> pushB, swapB, pushB, swapB, pushB, pushB.
	B: [3, 1, 0, 2 ...] -> pushB, revrotB, swapB, pushB, rotB, pushB, pushB.
	B: [3, 0, 1, 2 ...] -> pushB, revrotB, swapB, pushB, pushB, rotB, pushB.
	B: [2, 3, 1, 0 ...] -> pushB, pushB, swapB, pushB, pushB.
	B: [2, 3, 0, 1 ...] -> pushB, pushB, swapAB, pushB, pushB.
	B: [1, 3, 2, 0 ...] -> revrotB, pushB, pushB, rotB, pushB, pushB.
	B: [0, 3, 2, 1 ...] -> revrotB, pushB, pushB, pushB, rotB, pushB.
	B: [1, 3, 0, 2 ...] -> pushB, pushB, swapAB, pushB, swapA, pushB. 
	B: [0, 3, 1, 2 ...] -> pushB, pushB, swapAB, pushB swapA, pushB, swapA.
	B: [2, 1, 3, 0 ...] -> pushB, rotB, pushB, revrotB, swapA, pushB, pushB. 
	B: [2, 0, 3, 1 ...] -> pushB, rotB, pushB, revrotB, swapAB, pushB, pushB.
	B: [1, 2, 3, 0 ...] -> pushB, rotA, pushB, pushB, revrotA, pushB.
	B: [0, 2, 3, 1 ...] -> rotB, pushB, pushB, revrotB, swapAB, pushB, pushB.
	B: [1, 0, 3, 2 ...] -> pushB, revrotAB, pushB, pushB, swapB, rotAB, pushB.
	B: [0, 1, 3, 2 ...] -> pushB, pushB, swapA, rotA, rotA, pushB, pushB, revrotA, revrotA.
	B: [2, 1, 0, 3 ...] -> pushB, pushB, rotAB, pushB, revrotB, swapA, revrotA, pushB.
	B: [2, 0, 1, 3 ...] -> pushB, pushB, swapB, pushB, swapA, rotA, swapA, pushB, revrotA.
	B: [1, 2, 0, 3 ...] -> pushB, pushB, swapAB, pushB, swapA, rotA, swapA, revrotA, pushB.
	B: [0, 2, 1, 3 ...] -> pushB, pushB, swapAB, pushB, swapA, rotA, swapA, pushB, revrotA.
	B: [1, 0, 2, 3 ...] -> pushB, pushB, swapB, rotA, rotA, pushB, pushB, revrotA, revrotA.
	B: [0, 1, 2, 3 ...] -> pushB, pushB, swapAB, rotA, rotA, pushB, pushB, revrotA, revrotA.
*/

/*Range Split Algorithm simplified example:

A range of digits can be:
H=high, M=medium, L=low;
t=range_threshold_reached (depending on argc).

stack A:						stack B:					Action:
[unordered_digits]				[empty]						argv to stack A.
[H]								[M, L]						split A in 3.
[HH]							[HL, M, L]					split A in 2.
[HHHt]							[HHLt, HL, M, L]			split A in 2.
[HHt]							[HL, M, L]					split A in 2.
[HLH, HHt]						[HLLt, M, L]				split B in 2.
[HLHHt, HHt]					[HLHLt, HLLt, M, L]			push B.
[HLHs, HHt]						[HLLt, M, L]				push B.
[HLLs, HLHs, HHt]				[M, L]						push B.
[H]								[M, L]						etc for medium/low digits...

Conclusion:
- Initially split A into 3 ranges if argc > 6.
- Need to split A range? push lower half to B.
- Need to split B range? push upper half to A.
- If range digit count gets under certain threshold,
	we solve range using different different algorithm.
*/

/*Range Solve Algorithm:
4 ways to bring number from B to A: ra+rb, ra+rrb, rra+rb, rra+rrb;
	use the fewest moves way.
	repeat this until range.min is reached.
*/

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

//stacksize limit:
//your_ram - (SIZE_MAX/3 - (PS_RANGE_COUNT*16) - some_stack_variables).
typedef struct s_stack
{
	size_t			size;
	size_t			*prev;
	size_t			*next;
	size_t			a;
	size_t			b;
	t_range			ranges[PS_RANGE_COUNT];
	unsigned char	*fseq;
	size_t			fseqiterator;
	int				fd;
	void			(**fptrs)(struct s_stack *);
	const char		**foutput;
	const int		*foutputlen;
}	t_stack;

void	ps_printstack(char *str, size_t ptr, t_stack *stack);
void	ps_algorithm(t_stack *s);
void	ps_run(t_stack *s, unsigned char function);
bool	ps_displaymoves(t_stack *s);

//hchar functions :

unsigned char	ft_hchar_combine(unsigned char left, unsigned char right);
unsigned char	ft_hchar_getleft(unsigned char lefrig);
unsigned char	ft_hchar_getright(unsigned char lefrig);

//double linked circular list manipulation (pushswap0-3.c) :

//push stack x 'node' on top of stack y 'node' :
void	push_x_to_y(size_t *x, size_t *y, t_stack *s);

//swap this with s->next[this] :
void	swap(size_t *this, t_stack *s);

//rotate *this in dir direction
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
//		ra (rotate a):	Shift up all elements of stack a by 1.
//						The first element becomes the last one.
//		rb (rotate b):	Shift up all elements of stack b by 1.
//						The first element becomes the last one.
//		rr (rotate ab):	Shift up all elements of stack a and b by 1.
//		rra (reverse rotate a):		Shift down all elements of stack a by 1. The last element becomes the first one.
//		rrb (reverse rotate b):		Shift down all elements of stack b by 1. The last element becomes the first one.
//		rrr (reverse rotate ab):	Reverse Rotate a and b.