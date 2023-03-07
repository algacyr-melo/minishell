/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:11:01 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 18:18:21 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_argc(char **argv)
{
	size_t  argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

int handle_builtin(char **argv, char **envp, t_envl *env_lst)
{
	int argc;

	argc = get_argc(argv);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(argc, argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argc, argv, env_lst));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, env_lst));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(argv, env_lst));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (env(envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(argc, argv);
	return (-1);
}
