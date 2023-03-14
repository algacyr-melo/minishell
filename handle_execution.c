/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:54:04 by almelo            #+#    #+#             */
/*   Updated: 2023/03/14 16:47:58 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	deep_free(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst)
{
	char	**argv;
	char	**envp;
	char	*pathname;
	pid_t	pid;
	int		pipefd[2];
	int		prevpipe;

	prevpipe = dup(0);
	while (token_lst->head)
	{
		if (token_lst->head->label == PIPE)
			free(dequeue_token(token_lst));
		envp = list_to_envp(env_lst);
		argv = get_next_argv(token_lst);
		if (token_lst->head)
			pipe(pipefd);
		if (handle_builtin(argv, envp, env_lst) == -1)
		{
			pid = fork();
			if (pid == 0)
			{
				if (token_lst->head)
				{
					close(pipefd[0]);
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
				}
				dup2(prevpipe, STDIN_FILENO);
				close(prevpipe);
				pathname = get_pathname(argv, env_lst);
				if (execve(pathname, argv, envp) == -1)
					exit(0);
			}
			else
			{
				if (token_lst->head == NULL)
				{
					close(prevpipe);
					wait(&pid);
				}
				close(pipefd[1]);
				prevpipe = pipefd[0];
			}
		}
		free(argv);
		deep_free(envp);
	}
}
