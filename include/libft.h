/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doligtha <doligtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:09:51 by doligtha          #+#    #+#             */
/*   Updated: 2024/05/10 09:35:51 by doligtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>  // 'size_t';
# include <stdbool.h> // 'bool';

# ifndef ERROR_LIBFT
#  define ERROR_LIBFT -1
# endif

int		ft_printf(const char *format, ...);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_strchr(const char *s, int c);

//newly added:

// unsigned int ft_atou(const char *nptr)
// {
// 	unsigned int dest;
// 	unsigned int i;

// 	dest = 0;
// 	i = 0;
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		dest = dest * 10 + nptr[i];
// 		i++;
// 	}
// 	return (dest);
// }
void	ft_normalise_size(size_t *dst, size_t size);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strrstr(const char *big, const char *little);
void	ft_free(void **ptr);
void	ft_mapchr(char **map, char c, size_t *x, size_t *y);
size_t	ft_countwords(const char *str, const char *delims);

#endif //LIBFT_H
