/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:01:45 by almelo            #+#    #+#             */
/*   Updated: 2022/06/01 15:56:47 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int	len;

	if (!lst)
		return (0);
	len = 1;
	while (lst->next)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
//
//int	main(void)
//{
//	t_list	*head;
//
//	head = ft_lstnew("tandam");
//	ft_lstadd_front(&head, ft_lstnew("42"));
//	ft_lstadd_front(&head, ft_lstnew("www"));
//	printf("%d\n", ft_lstsize(head));
//	printf("%d\n", ft_lstsize(head));
//	return (0);
//}
