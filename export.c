/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:56:07 by almelo            #+#    #+#             */
/*   Updated: 2023/04/03 18:42:27 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_envl(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "?", 1) != 0)
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
}

static void	update_env(t_env *tmp, char *key, char *value)
{
	free(key);
	free(tmp->value);
	tmp->value = value;
}

int	ft_export(int argc, char **argv, char **envp, t_envl *env_lst)
{
	char	*key;
	char	*value;
	t_env	*tmp;
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
			update_env(tmp, key, value);
		else
			queue_env(env_lst, new_env(key, value));
		i++;
	}
	if (argc == 1)
		print_envl(envp);
	return (0);
}
