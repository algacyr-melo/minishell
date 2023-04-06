/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:26:43 by almelo            #+#    #+#             */
/*   Updated: 2023/04/06 14:27:16 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin_pp(char *cmd)
{
	return (ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

void	try_execute(char **argv, char **envp, t_envl *env_lst)
{
	char	*pathname;

	if (handle_builtin_cp(argv, envp) == -1)
	{
		pathname = get_pathname(argv, env_lst);
		if (pathname)
		{
			if (execve(pathname, argv, envp) == -1)
				exit(1);
		}
		else if (!is_builtin_pp(argv[0]))
		{
			printf("%s: command not found\n", argv[0]);
			g_exit_status = 127;
		}
	}
}
