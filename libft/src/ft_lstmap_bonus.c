/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:32:00 by almelo            #+#    #+#             */
/*   Updated: 2022/06/07 00:05:28 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_head;
	t_list	*node;

	list_head = NULL;
	while (lst)
	{
		node = ft_lstnew((*f)(lst->content));
		if (node == NULL)
			ft_lstclear(&list_head, (*del));
		ft_lstadd_back(&list_head, node);
		lst = lst->next;
	}
	return (list_head);
}
