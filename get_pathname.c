/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pathname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:58:56 by almelo            #+#    #+#             */
/*   Updated: 2023/03/22 19:36:12 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *path)
{
	return (ft_strcmp(path, "cd") == 0
		|| ft_strcmp(path, "export") == 0
		|| ft_strcmp(path, "unset") == 0
		|| ft_strcmp(path, "exit") == 0);
}

char	*get_pathname(char **argv, t_envl *env_lst)
{
	t_env	*path;
	char	**pathv;
	char	*pathname;
	size_t	i;

	if (is_builtin(argv[0]))
		return (NULL);
	if (access(argv[0], F_OK) == 0)
		return (argv[0]);
	path = get_env(env_lst, "PATH");
	pathv = ft_split(path->value, ':');
	argv[0] = ft_strjoin("/", argv[0]);
	i = 0;
	while (pathv[i])
	{
		pathname = ft_strjoin(pathv[i], argv[0]);
		if (access(pathname, F_OK) == 0)
			return (pathname);
		i++;
	}
	return (NULL);
}
