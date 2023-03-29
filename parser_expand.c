/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:40:36 by almelo            #+#    #+#             */
/*   Updated: 2023/03/29 18:56:29 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_keys(char *content)
{
	size_t			len;
	size_t			i;
	t_parser_state	state;

	state.prevent_default = FALSE;
	state.prevent_expand = FALSE;
	len = 0;
	i = 0;
	while (content[i])
	{
		if (is_quote(content[i]))
			update_parser_state(content, i, &state);
		else if ((content[i] == '$')
			&& ((state.prevent_expand == FALSE)
				|| ((state.prevent_default && state.prevent_expand == TRUE)
					&& content[0] == '\"')))
			len++;
		i++;
	}
	return (len);
}

void	handle_key(char *content, char **keys, t_index *i, enum e_bool *is_key)
{
	if (*is_key == FALSE)
		*is_key = TRUE;
	else if (*is_key == TRUE)
	{
		keys[i->key] = ft_substr(content, i->start, i->old - i->start);
		i->key++;
	}
	i->start = i->old + 1;
}

void	save_switch(char *content, char **key, t_index *i, enum e_bool *is_key)
{
	key[i->key] = ft_substr(content, i->start, i->old - i->start);
	i->key++;
	*is_key = FALSE;
}

void	expand_variable(t_envl *env_lst, char *key, char *new, t_index *i)
{
	t_env	*tmp;

	tmp = get_env(env_lst, key);
	ft_memcpy(&new[i->new], tmp->value, ft_strlen(tmp->value) + 1);
	i->old += ft_strlen(tmp->key) + 1;
	i->new += ft_strlen(tmp->value);
	i->key++;
}
