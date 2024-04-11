/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:34:03 by almelo            #+#    #+#             */
/*   Updated: 2023/04/06 14:34:30 by almelo           ###   ########.fr       */
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
		outfile = open(head->content, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		free(head->content);
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
		outfile = open(head->content, O_APPEND | O_CREAT | O_WRONLY, 0666);
		free(head->content);
		free(dequeue_token(token_lst));
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	return (bkp);
}

static void	handle_error(char *content)
{
	printf("minishell: %s: %s\n", content, strerror(errno));
	g_exit_status = errno;
}

void	handle_redirect_in(t_tokenl *token_lst, int prevpipe)
{
	int		infile;
	t_token	*head;

	while (token_lst->head && token_lst->head->label == IN)
	{
		free(dequeue_token(token_lst));
		head = token_lst->head;
		if (access(head->content, F_OK) == -1)
			handle_error((char *)head->content);
		else
		{
			infile = open(head->content, O_RDONLY);
			dup2(infile, prevpipe);
			close(infile);
		}
		free(head->content);
		free(dequeue_token(token_lst));
	}
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
	else if (token_lst->head->label == HEREDOC)
		handle_heredoc(token_lst, *prevpipe);
	return (bkp_stdout);
}
