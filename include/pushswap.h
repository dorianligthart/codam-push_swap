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
#  define PS_MAX_RANGE_SIZE 50
# endif

# ifndef PS_ERROR
#  define PS_ERROR 1
# endif

# ifndef PS_SUCCESS
#  define PS_SUCCESS 0
# endif

#include <unistd.h>
#include <stdbool.h>

//variable names for double circular linked list 'nodes'.
enum e_ps_pushswap
{
	PS_A,
	PS_B,
	PS_C,
	PS_D,
	PS_COUNT,
};

typedef struct s_ps_stack
{
	size_t	a;
	size_t	b;
	size_t	size;
	size_t	total_move_count;
}	t_ps_stack;

//DOUBLE CIRCULAR LINKED LIST, VIEWED AS ARRAYS.
//	- next[size], values pointing to the next in the list;
//	- prev[size], values pointing to the previous in the list; 
//example:
//	size = 5;
//	a	 = 2;
//	list = [4, 1, 3, 0, 2];
//	next = [1, 2, 3, 4, 0];
//	prev = [4, 0, 1, 2, 3];
//lets introduce b [2..4]:
//	a	 = 2;
//	b	 = 3;
//	list = [4, 1, 3, 0, 2];
//	next = [1, 0, 3, 4, 2];
//	prev = [1, 0, 4, 2, 3];
//
//this trick is done to let the data be small and we dont have much code.

void	printstacks(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_algorithm(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_pa(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_pb(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_sa(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_sb(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_ss(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_ra(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_rb(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_rr(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_rra(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_rrb(size_t *prev, size_t *next, t_ps_stack *stack);
bool	ps_rrr(size_t *prev, size_t *next, t_ps_stack *stack);

#endif //PUSHSWAP_H
