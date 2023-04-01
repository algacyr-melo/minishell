/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:45:23 by almelo            #+#    #+#             */
/*   Updated: 2023/03/31 23:47:30 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe_io(int *pipefd, int *prevpipe)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	dup2(*prevpipe, STDIN_FILENO);
	close(*prevpipe);
}

static void	set_output_to_prevpipe(int *pipefd, int *prevpipe)
{
	close(pipefd[1]);
	close(*prevpipe);
	*prevpipe = pipefd[0];
}

void	ft_pipe(char **argv, char **envp, t_envl *env_lst, int *prevpipe)
{
	pid_t	pid;
	int		pipefd[2];
	char	*pathname;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		set_pipe_io(pipefd, prevpipe);
		if (handle_builtin_cp(argv, envp) == -1)
		{
			pathname = get_pathname(argv, env_lst);
			if (pathname)
			{
				if (execve(pathname, argv, envp) == -1)
					exit(0);
			}
		}
		exit(0);
	}
	else
		set_output_to_prevpipe(pipefd, prevpipe);
}

void	ft_last(char **argv, char **envp, t_envl *env_lst, int *prevpipe)
{
	pid_t	pid;
	char	*pathname;

	pid = fork();
	if (pid == 0)
	{
		dup2(*prevpipe, STDIN_FILENO);
		close(*prevpipe);
		if (handle_builtin_cp(argv, envp) == -1)
		{
			pathname = get_pathname(argv, env_lst);
			if (pathname)
			{
				if (execve(pathname, argv, envp) == -1)
					exit(0);
			}
		}
		exit(0);
	}
	else
	{
		close(*prevpipe);
		while (wait(NULL) != -1)
			;
	}
}
