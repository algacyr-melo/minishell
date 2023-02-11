/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:50:50 by almelo            #+#    #+#             */
/*   Updated: 2023/02/11 17:58:11 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct s_node
{
	void			*value;
	struct s_node	*next;
}					t_node;

typedef struct s_envl
{
	t_node	*head;
}			t_envl;

#endif
