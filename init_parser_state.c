/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:02:45 by almelo            #+#    #+#             */
/*   Updated: 2023/03/29 18:46:59 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_keys(char *content)
{
	char			**key;
	size_t			key_counter;
	t_index			i;
	enum e_bool		is_key;
	t_quote_state	state;

	init_quote_state(&state);
	init_index(&i);
	is_key = FALSE;
	key_counter = count_keys(content);
	key = malloc((key_counter + 1) * sizeof(*key));
	while (i.key < key_counter)
	{
		if (is_quote(content[i.old]))
			update_quote_state(content, &i, &state);
		if ((content[i.old] == '$') && ((state.prevent_expand == FALSE)
				|| ((state.prevent_default && state.prevent_expand == TRUE)
					&& content[0] == '\"')))
			handle_key(content, key, &i, &is_key);
		else if (!ft_isalnum(content[i.old]) && is_key == TRUE)
			save_switch(content, key, &i, &is_key);
		i.old++;
	}
	key[i.key] = NULL;
	return (key);
}

size_t	new_content_len(char *content, t_envl *env_lst, char **keys)
{
	size_t	len_new_content;
	size_t	len_value;
	size_t	len_key;
	t_env	*tmp;
	size_t	i;

	len_new_content = ft_strlen(content);
	i = 0;
	while (keys[i])
	{
		tmp = get_env(env_lst, keys[i]);
		if (tmp)
		{
			len_value = ft_strlen(tmp->value);
			len_key = ft_strlen(tmp->key);
			len_new_content += (len_value - len_key - 1);
		}
		i++;
	}
	printf("%ld\n", len_new_content);
	len_new_content -= parse_quote_count(content);
	printf("%ld\n", len_new_content);
	return (len_new_content);
}

void	init_parser_state(t_parser_state *state, char *content, t_envl *env_lst)
{
	state->prevent_default = FALSE;
	state->prevent_expand = FALSE;
	state->keys = get_keys(content);
	state->len_new = new_content_len(content, env_lst, state->keys);
	state->new = malloc((state->len_new + 1) * sizeof(char));
}
