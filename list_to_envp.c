/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:58:10 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 17:00:17 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_key_value(char *key, char *value)
{
	char	*content;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	content = malloc((key_len + value_len + 2) * sizeof(*content));
	ft_memcpy(content, key, key_len + 1);
	content[key_len] = '=';
	ft_memcpy(content + key_len + 1, value, value_len + 1);
	return (content);
}

char	**list_to_envp(t_envl *env_lst)
{
	char	**envp;
	t_env	*tmp;
	size_t	i;

	//to do: fix malloc size
	envp = malloc((env_lst->length + 1) * sizeof(char *));
	tmp = env_lst->head;
	i = 0;
	while (i < env_lst->length)
	{
		envp[i] = join_key_value(tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
