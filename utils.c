/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:56:16 by almelo            #+#    #+#             */
/*   Updated: 2023/03/31 23:51:13 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_metachar(int c)
{
	return (ft_isspace(c) || is_operator(c));
}

int	is_quote(int c)
{
	return (c == '\"' || c == '\'');
}

void	init_index(t_index *i)
{
	i->key = 0;
	i->new = 0;
	i->old = 0;
	i->start = 0;
}

void	copy_char(char *new_content, char *content, t_index *i)
{
	new_content[i->new] = content[i->old];
	i->new++;
	i->old++;
}
