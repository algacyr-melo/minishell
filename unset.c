/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:00:34 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 18:02:13 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to do: handle removal for first node
static t_env	*remove_env(t_envl *env_lst, char *key)
{
	t_env   *tmp;
	t_env   *node;

	tmp = env_lst->head;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->next->key, key) == 0)
		{
			node = tmp->next;
			tmp->next = tmp->next->next;
			env_lst->length--;
			return (node);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int unset(char **argv, t_envl *env_lst)
{
	char    *key;
	t_env   *tmp;

	key = argv[1];
	tmp = remove_env(env_lst, key);
	if (tmp)
		free(tmp);
	return (0);
}
