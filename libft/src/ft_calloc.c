/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:29:46 by almelo            #+#    #+#             */
/*   Updated: 2022/05/31 17:55:47 by almelo           ###   ########.fr       */
/*   Updated: 2022/05/26 11:08:33 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	buffer = malloc(count * size);
	if (!buffer)
		return (0);
	ft_bzero(buffer, (count * size));
	return (buffer);
}
