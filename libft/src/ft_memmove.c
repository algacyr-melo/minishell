/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:30:50 by almelo            #+#    #+#             */
/*   Updated: 2022/05/30 21:07:12 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*temp_dst;
	const char	*temp_src;

	temp_dst = dst;
	temp_src = src;
	if (temp_dst < temp_src)
		ft_memcpy(dst, src, len);
	else
	{
		temp_dst += (len - 1);
		temp_src += (len - 1);
		while (len--)
			*temp_dst-- = *temp_src--;
	}
	return (dst);
}
