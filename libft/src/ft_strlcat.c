/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:10:42 by almelo            #+#    #+#             */
/*   Updated: 2022/05/28 11:19:42 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t				dst_len;
	unsigned int		i;
	unsigned int		limit;

	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + ft_strlen(src));
	limit = dstsize - dst_len - 1;
	i = 0;
	while (*(src + i) && i < limit)
	{
		*(dst + dst_len + i) = *(src + i);
		i++;
	}
	*(dst + dst_len + i) = '\0';
	return (dst_len + ft_strlen(src));
}
