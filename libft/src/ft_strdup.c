/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:22:36 by almelo            #+#    #+#             */
/*   Updated: 2022/05/30 22:07:11 by almelo           ###   ########.fr       */
/*   Updated: 2022/05/26 11:31:56 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*copy_s;
	size_t			len_s;
	unsigned int	i;

	len_s = ft_strlen(s);
	copy_s = malloc((len_s + 1) * sizeof(char));
	if (copy_s == NULL)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(copy_s + i) = *(s + i);
		i++;
	}
	*(copy_s + i) = '\0';
	return (copy_s);
}
