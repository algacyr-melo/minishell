/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:57:24 by almelo            #+#    #+#             */
/*   Updated: 2023/03/10 12:33:33 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_cmd_len(t_tokenl *token_lst)
{
	size_t	len;
	t_token	*tmp;

	tmp = token_lst->head;
	len = 0;
	while (tmp && tmp->content)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

char	**get_next_argv(t_tokenl *token_lst)
{
	char	**argv;
	size_t	i;
	size_t	cmd_len;

	cmd_len = get_cmd_len(token_lst);
	argv = malloc((cmd_len + 1) * sizeof(char *));
	i = 0;
	while (token_lst->head && token_lst->head->content)
	{
		argv[i] = (char *)token_lst->head->content;
		free(dequeue_token(token_lst));
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
