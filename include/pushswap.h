/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:22 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/09 03:29:19 by doligtha         ###   ########.fr       */
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

//DOUBLE CIRCULAR LINKED LIST, VIEWED AS ARRAYS.
//	- next[size], values pointing to the next in the list;
//	- prev[size], values pointing to the previous in the list; 
typedef struct s_dcllist
{
	size_t		*next;
	size_t		*prev;
	size_t		size;
}	t_dcllist;
//example:
//	normal_list		= [4, 1, 3, 0, 2];
//	index_val_swap	= [3, 1, 4, 2, 0];
//	next			= [2, 3, 4, 0, 1];
//	prev			= [3, 4, 0, 1, 2];
//						\/ swap
// this trick is done to let the data be small so we dont have much code. 

	// size_t	range_count;
	// size_t	range_size;
	// size_t	range_mod;

void	ps_printstacks(t_dcllist *s, size_t a, size_t b);
bool	ps_algorithm(t_dcllist *s, size_t a);

bool	ps_pa(t_dcllist *s);
bool	ps_pb(t_dcllist *s);
bool	ps_sa(t_dcllist *s);
bool	ps_sb(t_dcllist *s);
bool	ps_ss(t_dcllist *s);
bool	ps_ra(t_dcllist *s);
bool	ps_rb(t_dcllist *s);
bool	ps_rr(t_dcllist *s);
bool	ps_rra(t_dcllist *s);
bool	ps_rrb(t_dcllist *s);
bool	ps_rrr(t_dcllist *s);

#endif //PUSHSWAP_H
