/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:35:52 by almelo            #+#    #+#             */
/*   Updated: 2022/05/30 19:36:42 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char		*temp_src;
	char			*temp_dst;
	unsigned int	i;

	temp_src = src;
	temp_dst = dst;
	i = 0;
	while (i < n)
	{
		*(temp_dst + i) = *(temp_src + i);
		i++;
	}
	return (dst);
}
