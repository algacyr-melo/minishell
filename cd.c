/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:35 by almelo            #+#    #+#             */
/*   Updated: 2023/03/09 12:26:30 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd(int argc, char **argv, t_envl *env_lst)
{
    char    *path;
	t_env	*oldpwd;
	t_env	*pwd;

	oldpwd = get_env(env_lst, "OLDPWD");
	pwd = get_env(env_lst, "PWD");
	oldpwd->value = pwd->value;
    if (argc == 1)
        path = env_lst->home->value;
    else
        path = argv[1];
    if (chdir(path) == -1)
    {
        printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
        return (errno);
    }
	pwd->value = getcwd(NULL, 0);
    return (0);
}
