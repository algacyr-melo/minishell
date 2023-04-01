/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:34:03 by almelo            #+#    #+#             */
/*   Updated: 2023/04/01 19:44:46 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		outfile;
	int		bkp;
	t_token	*head;

	bkp = dup(STDOUT_FILENO);
	while (token_lst->head && token_lst->head->label == APPEND)
	{
		free(dequeue_token(token_lst));
		free(dequeue_token(token_lst));
		head = token_lst->head;
		outfile = open(head->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(dequeue_token(token_lst));
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	return (bkp);
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

void	handle_heredoc(t_tokenl *token_lst, t_envl *env_lst, int prevpipe)
{
	char	*input;
	//char	*tmp;
	char	*delimiter;
	int		pipefd[2];

	(void)env_lst;
	free(dequeue_token(token_lst));
	free(dequeue_token(token_lst));
	delimiter = token_lst->head->content;
	pipe(pipefd);
	while (42)
	{
		input = readline("> ");
		if (ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			exit(0) ;
		}
		//tmp = parse_content(input, env_lst);
		ft_putendl_fd(input, pipefd[1]);
		free(input);
	}
	dup2(pipefd[0], prevpipe);
	close(pipefd[0]);
	close(pipefd[1]);
	free(dequeue_token(token_lst));
}

int	handle_redirect(t_tokenl *token_lst, t_envl *env_lst, int *prevpipe)
{
	int	bkp_stdout;

	bkp_stdout = dup(STDOUT_FILENO);
	if (token_lst->head->label == IN)
		handle_redirect_in(token_lst, *prevpipe);
	else if (token_lst->head->label == OUT)
		bkp_stdout = handle_redirect_out(token_lst);
	else if (token_lst->head->label == APPEND)
		bkp_stdout = handle_append(token_lst);
	else if (token_lst->head->label == HEREDOC)
		handle_heredoc(token_lst, env_lst, *prevpipe);
	return (bkp_stdout);
}
