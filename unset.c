/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:00:34 by almelo            #+#    #+#             */
/*   Updated: 2023/03/16 01:36:25 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_env(t_envl *env_lst, char *key)
{
	t_env   *tmp;
	t_env	*prev;

	tmp = env_lst->head;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				env_lst->head = tmp->next;
			env_lst->length--;
			return (tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

int unset(char **argv, t_envl *env_lst)
{
	char    *key;
	t_env   *tmp;
	size_t	i;

	i = 1;
	while (argv[i])
	{
		key = argv[i];
		tmp = remove_env(env_lst, key);
		if (tmp)
		{
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		i++;
	}
	return (0);
}
