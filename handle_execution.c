/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:54:04 by almelo            #+#    #+#             */
/*   Updated: 2023/03/31 23:09:28 by almelo           ###   ########.fr       */
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

void	handle_redirect_in(t_tokenl *token_lst, int prevpipe)
{
	int	fd_infile;

	while (token_lst->head && token_lst->head->label == IN)
	{
		free(dequeue_token(token_lst));
		fd_infile = open(token_lst->head->content, O_RDONLY);
		free(dequeue_token(token_lst));
		dup2(fd_infile, prevpipe);
	}
}

int	handle_redirect_out(t_tokenl *token_lst)
{
	int		outfile;
	int		bkp;
	t_token	*head;

	bkp = dup(STDOUT_FILENO);
	while (token_lst->head && token_lst->head->label == OUT)
	{
		free(dequeue_token(token_lst));
		head = token_lst->head;
		outfile = open(head->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(dequeue_token(token_lst));
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	return (bkp);
}

int	handle_append(t_tokenl *token_lst)
{
	int	outfile;
	int	bkp;

	bkp = dup(STDOUT_FILENO);
	while (token_lst->head && token_lst->head->label == APPEND)
	{
		free(dequeue_token(token_lst));
		free(dequeue_token(token_lst));
		outfile = open(token_lst->head->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(dequeue_token(token_lst));
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	return (bkp);
}

int	handle_redirect(t_tokenl *token_lst, int *prevpipe)
{
	int	bkp_stdout;

	bkp_stdout = dup(STDOUT_FILENO);
	if (token_lst->head->label == IN)
		handle_redirect_in(token_lst, *prevpipe);
	else if (token_lst->head->label == OUT)
		bkp_stdout = handle_redirect_out(token_lst);
	else if (token_lst->head->label == APPEND)
		bkp_stdout = handle_append(token_lst);
	return (bkp_stdout);
}

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst)
{
	char	**argv;
	char	**envp;
	int		prevpipe;
	int		bkp_stdout;

	prevpipe = dup(STDIN_FILENO);
	bkp_stdout = dup(STDOUT_FILENO);
	while (token_lst->head)
	{
		envp = list_to_envp(env_lst);
		argv = get_next_argv(token_lst);
		if (token_lst->head)
			bkp_stdout = handle_redirect(token_lst, &prevpipe);
		env_lst = handle_builtin_pp(argv, envp, env_lst);
		if (token_lst->pipe_count > 0)
		{
			ft_pipe(argv, envp, env_lst, &prevpipe);
			free(dequeue_token(token_lst));
		}
		else
			ft_last(argv, envp, env_lst, &prevpipe);
		dup2(bkp_stdout, STDOUT_FILENO);
		deep_free(envp);
		deep_free(argv);
	}
}
