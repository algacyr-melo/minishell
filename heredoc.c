/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:16:17 by almelo            #+#    #+#             */
/*   Updated: 2023/04/06 15:34:23 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(int *pipefd, char *del, char *warning_msg)
{
	char	*input;

	close(pipefd[0]);
	set_signal_handler_child();
	while (42)
	{
		input = readline("> ");
		if ((input == NULL) || (ft_strcmp(input, del) == 0))
		{
			if (input == NULL)
				printf("minishell: %s (wanted `%s')\n", warning_msg, del);
			free(input);
			exit(0);
		}
		ft_putendl_fd(input, pipefd[1]);
		free(input);
	}
}

void	redirect_input(int *pipefd, int prevpipe)
{
	int	status;

	close(pipefd[1]);
	wait(&status);
	dup2(pipefd[0], prevpipe);
	close(pipefd[0]);
	g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_heredoc(t_tokenl *token_lst, int prevpipe)
{
	char	*delimiter;
	int		pipefd[2];
	pid_t	pid;
	char	*warning_msg;

	free(dequeue_token(token_lst));
	free(dequeue_token(token_lst));
	delimiter = token_lst->head->content;
	warning_msg = ft_strdup("warning : heredoc delimited by EOF");
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
		read_input(pipefd, delimiter, warning_msg);
	else
		redirect_input(pipefd, prevpipe);
	free(dequeue_token(token_lst));
	free(delimiter);
	free(warning_msg);
}
