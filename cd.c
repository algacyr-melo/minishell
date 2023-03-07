/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:51:35 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 17:52:08 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to do: update OLDPWD & PWD
int cd(int argc, char **argv, t_envl *env_lst)
{
    char    *path;

    if (argc == 1)
        path = env_lst->home->value;
    else
        path = argv[1];
    if (chdir(path) == -1)
    {
        printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
        return (errno);
    }
    return (0);
}
