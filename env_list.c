/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:37:10 by almelo            #+#    #+#             */
/*   Updated: 2023/02/11 19:38:02 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*new_node(void *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->value = value;
	node->next = NULL;
	return (node);
}

static void	push(t_envl *env_lst, t_node *new)
{
	if (env_lst->head == NULL)
		env_lst->head = new;
	else
	{
		new->next = env_lst->head;
		env_lst->head = new;
	}
}

void	create_env_list(t_envl *env_lst, char **envp)
{
	size_t	i;

	env_lst->head = NULL;
	i = 0;
	while (*(envp + i))
	{
		push(env_lst, new_node(envp[i])); 
		i++;
	}
}
