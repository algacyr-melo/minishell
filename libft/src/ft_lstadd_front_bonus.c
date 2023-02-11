/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:14:46 by almelo            #+#    #+#             */
/*   Updated: 2022/06/06 16:43:48 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

//int	main(void)
//{
//	char	*s1;
//	char	*s2;
//	char	*s3;
//	char	*s4;
//	//int		arr[] = { 4, 2, 0, -1 };
//	t_list	*list;
//
//	s1 = "Hello!";
//	s2 = "lst";
//	s3 = "42";
//	s4 = "\tbonus\t";
//
//	ft_lstadd_back(&list, ft_lstnew(s4));
//	printf("%s\n", list->content);
//	return (0);
//}
