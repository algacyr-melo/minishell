/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:54:04 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 18:12:19 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst)
{
	char	**argv;
	char	**envp;
	char	*pathname;
	pid_t	pid;

	envp = list_to_envp(env_lst);
	argv = get_next_argv(token_lst);
	if (handle_builtin(argv, envp, env_lst) == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			pathname = get_pathname(argv, env_lst);
			if (execve(pathname, argv, envp) == -1)
				exit(0);
		}
		else
			wait(&pid);
	}
	free(envp);
}
