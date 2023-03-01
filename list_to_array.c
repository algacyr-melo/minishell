/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:57:24 by almelo            #+#    #+#             */
/*   Updated: 2023/03/01 17:26:56 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*dequeue_token(t_tokenl *token_lst)
{
	t_token	*head;

	head = token_lst->head;
	if (token_lst->length > 1)
	{
		token_lst->head = head->next;
		head->next = NULL;
	}
	else
	{
		token_lst->head = NULL;
		token_lst->tail = NULL;
	}
	token_lst->length--;
	return (head);
}

char	**list_to_array(t_tokenl *token_lst)
{
	char	**argv;
	size_t	i;

	argv = malloc((token_lst->length + 1) * sizeof(char *));
	i = 0;
	while (token_lst->length > 0 && token_lst->head->content)
	{
		argv[i] = (char *)token_lst->head->content;
		dequeue_token(token_lst);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
