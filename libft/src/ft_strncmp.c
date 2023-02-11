/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 09:49:24 by almelo            #+#    #+#             */
/*   Updated: 2022/05/30 21:33:34 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	i = 0;
	while ((*(s1 + i) || *(s2 + i)) && i < n)
	{
		if (*(u_s1 + i) != *(u_s2 + i))
			return (*(u_s1 + i) - *(u_s2 + i));
		i++;
	}
	return (0);
}
