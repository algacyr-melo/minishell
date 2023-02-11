/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:07:38 by almelo            #+#    #+#             */
/*   Updated: 2022/06/01 11:56:33 by almelo           ###   ########.fr       */
/*   Updated: 2022/05/26 17:04:10 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strflen(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (*(str + len) != c && *(str + len))
		len++;
	return (len);
}

static unsigned int	ft_count_elem(char const *s, char c)
{
	unsigned int	n_elem;
	unsigned int	i;
	int				flag;

	flag = 1;
	n_elem = 0;
	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			flag = 1;
		else if (flag == 1)
		{
			n_elem++;
			flag = 0;
		}
		i++;
	}
	return (n_elem);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	unsigned int	i;
	unsigned int	arr_i;
	unsigned int	n_elem;

	if (!s)
		return (0);
	n_elem = ft_count_elem(s, c);
	arr = ft_calloc((n_elem + 1), sizeof(char *));
	arr_i = 0;
	i = 0;
	while (arr_i < n_elem)
	{
		if (*(s + i) == c)
			i++;
		else
		{	
			*(arr + arr_i) = ft_substr(s, i, ft_strflen(s + i, c));
			i += ft_strlen(*(arr + arr_i));
			arr_i++;
		}
	}
	*(arr + arr_i) = 0;
	return (arr);
}
