/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:00:34 by almelo            #+#    #+#             */
/*   Updated: 2023/03/20 22:28:28 by dioda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_env(t_envl *env_lst, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env_lst->head;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				env_lst->head = tmp->next;
			else
			{
				if (tmp->next == NULL)
					env_lst->tail = prev;
				prev->next = tmp->next;
			}
			env_lst->length--;
			return (tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

int	unset(char **argv, t_envl *env_lst)
{
	char	*key;
	t_env	*tmp;
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
