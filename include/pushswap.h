/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:53:22 by doligtha          #+#    #+#             */
/*   Updated: 2024/04/20 23:15:19 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# ifndef PS_ERROR
#  define PS_ERROR 1
# endif

// origin	= ft_atoi(argv items);
// stack[]	= stack A and B normalised values;
// size		= sizeof(stack);
// a_next[]	= value is index to next element stack A;
// a_prev[]	= value is index to previous element stack A;
// b_next[]	= value is index to next element stack B;
// b_prev[]	= value is index to previous element stack B;
// a_ptr	= value is index to HEAD of stack A;
// b_ptr	= value is index to HEAD of stack B;
typedef struct s_ps_stack
{
	int				*origin;
	unsigned int	*stack;
	unsigned int	*a_next;
	unsigned int	*a_prev;
	unsigned int	*b_next;
	unsigned int	*b_prev;
	unsigned int	size;
	unsigned int	a_ptr;
	unsigned int	b_ptr;
	unsigned int	*groups;
}	t_ps_stack;

void	ps_init(t_ps_stack *s);
void	ps_pa(t_ps_stack *s);
void	ps_pb(t_ps_stack *s);
void	ps_sa(t_ps_stack *s);
void	ps_sb(t_ps_stack *s);
void	ps_ss(t_ps_stack *s);
void	ps_ra(t_ps_stack *s);
void	ps_rb(t_ps_stack *s);
void	ps_rr(t_ps_stack *s);
void	ps_rra(t_ps_stack *s);
void	ps_rrb(t_ps_stack *s);
void	ps_rrr(t_ps_stack *s);

#endif //PUSHSWAP_H
