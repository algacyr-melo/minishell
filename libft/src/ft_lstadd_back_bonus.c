/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:00:20 by almelo            #+#    #+#             */
/*   Updated: 2022/06/06 22:34:43 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL && new)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		ft_lstlast(*lst)->next = new;
		ft_lstlast(new)->next = NULL;
	}
}
