/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:37:44 by almelo            #+#    #+#             */
/*   Updated: 2023/04/06 14:38:27 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append_syntax(t_token *curr, t_token *prev)
{
	if (prev == NULL || curr->next->next == NULL
		|| curr->next->label != WORD || prev->label != WORD)
	{
		printf("minishell: syntax error near unexpected token `>>'\n");
		return (2);
	}
	return (0);
}

int	handle_heredoc_syntax(t_token *curr, t_token *prev)
{
	if (prev == NULL || curr->next->next == NULL
		|| curr->next->next->label != WORD || prev->label != WORD)
	{
		printf("minishell: syntax error near unexpected token `<<'\n");
		return (2);
	}
	return (0);
}

int	check_syntax(t_tokenl *token_lst)
{
	t_token	*curr;
	t_token	*prev;

	prev = NULL;
	curr = token_lst->head;
	while (curr)
	{
		if (curr->label == PIPE || curr->label == IN || curr->label == OUT)
		{
			if (prev == NULL || curr->next == NULL
				|| curr->next->label != WORD
				|| prev->label != WORD)
			{
				printf("minishell: syntax error\n");
				return (2);
			}
		}
		else if (curr->label == APPEND)
			return (handle_append_syntax(curr, prev));
		else if (curr->label == HEREDOC)
			return (handle_heredoc_syntax(curr, prev));
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
