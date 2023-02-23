/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 12:11:59 by almelo            #+#    #+#             */
/*   Updated: 2023/02/23 19:29:26 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_token(t_tokenl *token_lst, t_token *new)
{
	if (token_lst->head == NULL)
	{
		token_lst->head = new;
		token_lst->tail = new;
		token_lst->length = 0;
	}
	else
	{
		token_lst->tail->next = new;
		token_lst->tail = new;
	}
	token_lst->length++;
}

t_token	*new_token(void *content, enum e_label label)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->content = content;
	token->label = label;
	token->next = NULL;
	return (token);
}
