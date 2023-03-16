/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:56:07 by almelo            #+#    #+#             */
/*   Updated: 2023/03/15 23:23:28 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_envl(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
}

int ft_export(int argc, char **argv, char **envp, t_envl *env_lst)
{
	char    *key;
	char    *value;
	t_env   *tmp;
	size_t	i;

	i = 1;
	while (argv[i])
	{
		key = get_key(argv[i]);
		value = get_value(argv[i]);
		if (key == NULL || value == NULL)
		{
			i++;
			continue ;
		}
		tmp = get_env(env_lst, key);
		if (tmp)
		{
			free(key);
			free(tmp->value);
			tmp->value = value;
		}
		else
			queue_env(env_lst, new_env(key, value));
		i++;
	}
	if (argc == 1)
		print_envl(envp);
	return (0);
}
