/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:22 by doligtha          #+#    #+#             */
/*   Updated: 2024/04/12 01:43:08 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <math.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

# ifndef PS_ERROR
#  define PS_ERROR 1
# endif

typedef struct s_ps_stack
{
	unsigned int	*stack;
	unsigned int	*next;
	unsigned int	*prev;
	unsigned int	size;
	unsigned int	ptr;
}	t_ps_stack;

bool	ps_algorithm(t_ps_stack *a, t_ps_stack *b, unsigned int size);

void	ps_pa(t_ps_stack *a, t_ps_stack *b);
void	ps_pb(t_ps_stack *a, t_ps_stack *b);
void	ps_sa(t_ps_stack *a, t_ps_stack *b);
void	ps_sb(t_ps_stack *a, t_ps_stack *b);
void	ps_ss(t_ps_stack *a, t_ps_stack *b);
void	ps_ra(t_ps_stack *a, t_ps_stack *b);
void	ps_rb(t_ps_stack *a, t_ps_stack *b);
void	ps_rr(t_ps_stack *a, t_ps_stack *b);
void	ps_rra(t_ps_stack *a, t_ps_stack *b);
void	ps_rrb(t_ps_stack *a, t_ps_stack *b);
void	ps_rrr(t_ps_stack *a, t_ps_stack *b);

#endif //PUSHSWAP_H
