/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:57:24 by almelo            #+#    #+#             */
/*   Updated: 2023/02/25 15:57:53 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_array(t_tokenl *token_lst)
{
	char	**argv;
	t_token	*tmp;
	size_t	i;

	argv = malloc((token_lst->length + 1) * sizeof(char *));
	tmp = token_lst->head;
	i = 0;
	while (i < token_lst->length)
	{
		argv[i] = (char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
