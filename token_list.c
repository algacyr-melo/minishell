/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 12:11:59 by almelo            #+#    #+#             */
/*   Updated: 2023/02/19 13:41:52 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_token(t_tokenl *token_lst, t_token *new)
{
	if (token_lst->head == NULL)
		token_lst->head = new;
	else
	{
		new->next = token_lst->head;
		token_lst->head = new;
	}
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
