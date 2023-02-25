/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:07:13 by almelo            #+#    #+#             */
/*   Updated: 2023/02/25 16:09:26 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_envl *env_lst)
{
	t_env_node	*head;
	t_env_node	*tmp;

	head = env_lst->head;
	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_token_list(t_tokenl *token_lst)
{
	t_token	*head;
	t_token	*tmp;

	head = token_lst->head;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
