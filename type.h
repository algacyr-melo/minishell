/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:50:50 by almelo            #+#    #+#             */
/*   Updated: 2023/02/15 13:32:35 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct s_env_node
{
	void				*key;
	void				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_envl
{
	t_env_node	*head;
}				t_envl;

enum e_token
{
	WORD,
	OP,
};

enum e_bool
{
	FALSE,
	TRUE,
};

typedef struct s_token
{
	void			*content;
	enum e_token	token;
	struct s_token	*next;
}						t_token;

typedef struct s_tokenl
{
	t_token	*head;
}			t_tokenl;
#endif
