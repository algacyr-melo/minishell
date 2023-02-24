/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:50:50 by almelo            #+#    #+#             */
/*   Updated: 2023/02/24 18:03:44 by almelo           ###   ########.fr       */
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
	t_env_node	*tail;
	t_env_node	*path;
	size_t		length;
}				t_envl;

enum e_label
{
	WORD,
	PIPE,
	IN,
	OUT,
};

enum e_bool
{
	FALSE,
	TRUE,
};

typedef struct s_lexer_state
{
	char		*input_copy;
	size_t		start;
	enum e_bool	is_word;
	enum e_bool	is_quoted;
}				t_lexer_state;

typedef struct s_token
{
	void			*content;
	enum e_label	label;
	struct s_token	*next;
}					t_token;

typedef struct s_tokenl
{
	t_token	*head;
	t_token	*tail;
	size_t	length;
}			t_tokenl;
#endif
