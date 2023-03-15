/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:11:01 by almelo            #+#    #+#             */
/*   Updated: 2023/03/15 18:18:03 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_argc(char **argv)
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
		echo(argc, argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argc, argv, envp, env_lst);
	else if (ft_strcmp(argv[0], "unset") == 0)
		unset(argv, env_lst);
	else if (ft_strcmp(argv[0], "env") == 0)
		env(envp);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(argc, argv);
	return (-1);
}
