/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 23:34:03 by almelo            #+#    #+#             */
/*   Updated: 2023/03/31 23:40:34 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
