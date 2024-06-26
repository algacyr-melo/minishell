/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:35 by almelo            #+#    #+#             */
/*   Updated: 2023/04/03 16:36:18 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_oldpwd(t_envl *env_lst, t_env *oldpwd)
{
	if (oldpwd == NULL)
		queue_env(env_lst, new_env(ft_strdup("OLDPWD"), getcwd(NULL, 0)));
	else
	{
		free(oldpwd->value);
		oldpwd->value = getcwd(NULL, 0);
	}
}

static void	set_pwd(t_envl *env_lst, t_env *pwd)
{
	if (pwd == NULL)
		queue_env(env_lst, new_env(ft_strdup("PWD"), getcwd(NULL, 0)));
	else
	{
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
}

int	cd(int argc, char **argv, t_envl *env_lst)
{
	char	*path;
	t_env	*oldpwd;
	t_env	*pwd;
	t_env	*home;

	oldpwd = get_env(env_lst, "OLDPWD");
	set_oldpwd(env_lst, oldpwd);
	if (argc == 1)
	{
		home = get_env(env_lst, "HOME");
		if (home)
			path = home->value;
		else
			return (1);
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
		return (errno);
	}
	pwd = get_env(env_lst, "PWD");
	set_pwd(env_lst, pwd);
	return (0);
}
