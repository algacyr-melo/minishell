/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:37:10 by almelo            #+#    #+#             */
/*   Updated: 2023/02/14 16:35:45 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_node	*new_env_node(void *key, void *value)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

static void	push_env(t_envl *env_lst, t_env_node *new)
{
	if (env_lst->head == NULL)
		env_lst->head = new;
	else
	{
		new->next = env_lst->head;
		env_lst->head = new;
	}
}

char	*get_key(char *env_str)
{
	char	*key;
	char	*separator;
	size_t	len;

	separator = ft_strchr(env_str, '=');
	len = separator - env_str;
	key = ft_substr(env_str, 0, len);
	return (key);
}

char	*get_value(char *env_str)
{
	char	*value;
	char	*separator;
	size_t	len;

	separator = ft_strchr(env_str, '=');
	len = env_str + (ft_strlen(env_str) - 1) - separator;
	value = ft_substr(env_str, (separator + 1) - env_str, len);
	return (value);
}

void	create_env_list(t_envl *env_lst, char **envp)
{
	size_t	i;
	char	*key;
	char	*value;

	env_lst->head = NULL;
	i = 0;
	while (*(envp + i))
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		push_env(env_lst, new_env_node(key, value));
		i++;
	}
}