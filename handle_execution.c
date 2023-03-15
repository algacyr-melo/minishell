/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:54:04 by almelo            #+#    #+#             */
/*   Updated: 2023/03/14 23:26:32 by almelo           ###   ########.fr       */
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

void	handle_pipe(char **argv, char **envp, t_envl *env_lst, int *prevpipe)
{
	pid_t	pid;
	int		pipefd[2];
	char	*pathname;

	pipe(pipefd);
	//handle_builtin(argv, envp, env_lst);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		dup2(*prevpipe, STDIN_FILENO);
		close(*prevpipe);
		pathname = get_pathname(argv, env_lst);
		if (execve(pathname, argv, envp) == -1)
			exit(0);
	}
	else
	{
		close(pipefd[1]);
		close(*prevpipe);
		*prevpipe = pipefd[0];
	}
}

void	handle_last_cmd(char **argv, char **envp, t_envl *env_lst, int *prevpipe)
{
	pid_t	pid;
	char	*pathname;

	pid = fork();
	//handle_builtin(argv, envp, env_lst);
	if (pid == 0)
	{
		dup2(*prevpipe, STDIN_FILENO);
		close(*prevpipe);
		pathname = get_pathname(argv, env_lst);
		if (execve(pathname, argv, envp) == -1)
			exit(0);
	}
	else
	{
		close(*prevpipe);
		while (wait(NULL) != -1)
			;
	}
}

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst)
{
	char	**argv;
	char	**envp;
	int		prevpipe;

	prevpipe = dup(STDIN_FILENO);
	while (token_lst->head)
	{
		if (token_lst->head->label == PIPE)
			free(dequeue_token(token_lst));
		envp = list_to_envp(env_lst);
		argv = get_next_argv(token_lst);
		if (token_lst->head)
			handle_pipe(argv, envp, env_lst, &prevpipe);
		else
			handle_last_cmd(argv, envp, env_lst, &prevpipe);
		free(argv);
		deep_free(envp);
	}
}
