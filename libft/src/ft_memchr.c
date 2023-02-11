/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:08:51 by almelo            #+#    #+#             */
/*   Updated: 2022/05/30 21:39:56 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*temp_s;
	unsigned int		i;

	temp_s = s;
	i = 0;
	while (i < n)
	{
		if (*(temp_s + i) == (unsigned char)c)
			return ((char *)(temp_s + i));
		i++;
	}
	return (0);
}
