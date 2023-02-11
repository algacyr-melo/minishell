/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 09:09:44 by almelo            #+#    #+#             */
/*   Updated: 2022/05/30 22:22:59 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	len;
	unsigned int	i;
	unsigned int	offset;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		offset = len - i;
		if (*(s + offset) == (unsigned char)c)
			return ((char *)(s + offset));
		i++;
	}
	return (0);
}
