/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:20:02 by almelo            #+#    #+#             */
/*   Updated: 2022/06/06 23:34:05 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*temp;

	node = *lst;
	while (node->next)
	{
		(*del)(node->content);
		temp = node->next;
		free(node);
		node = temp;
	}
	ft_lstdelone(node, &free);
	*lst = NULL;
}
