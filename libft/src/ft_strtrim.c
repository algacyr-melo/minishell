/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:06:10 by almelo            #+#    #+#             */
/*   Updated: 2022/05/31 17:52:17 by almelo           ###   ########.fr       */
/*   Updated: 2022/05/26 15:20:39 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_get_offset(char const *str, char const *set)
{
	unsigned int	offset;
	unsigned int	set_i;

	offset = 0;
	set_i = 0;
	while (*(set + set_i))
	{
		if (*(str + offset) == *(set + set_i))
		{
			offset++;
			set_i = 0;
			continue ;
		}
		set_i++;
	}
	return (offset);
}

static unsigned int	ft_get_roffset(char const *str, char const *set)
{
	unsigned int	start_offset;
	unsigned int	offset;
	unsigned int	set_i;

	start_offset = ft_strlen(str) - 1;
	offset = start_offset;
	set_i = 0;
	while (*(set + set_i))
	{
		if (*(str + offset) == *(set + set_i))
		{
			offset--;
			set_i = 0;
			continue ;
		}
		set_i++;
	}
	return (start_offset - offset);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	l_offset;
	unsigned int	r_offset;
	size_t			t_len;
	char			*buffer;

	l_offset = ft_get_offset(s1, set);
	if (l_offset == ft_strlen(s1))
	{
		buffer = ft_strdup("\0");
		if (!buffer)
			return (0);
		return (buffer);
	}
	r_offset = ft_get_roffset(s1, set);
	t_len = ft_strlen(s1) - (l_offset + r_offset);
	buffer = ft_substr(s1, l_offset, t_len);
	if (!buffer)
		return (0);
	return (buffer);
}
