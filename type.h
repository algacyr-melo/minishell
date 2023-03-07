/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:50:50 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 00:31:05 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

enum e_label
{
	WORD,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
};

enum e_bool
{
	FALSE,
	TRUE,
};

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

typedef struct s_env
{
	void			*key;
	void			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_envl
{
	t_env	*head;
	t_env	*tail;
	t_env	*path;
	t_env	*home;
	size_t	length;
}			t_envl;

typedef struct s_lexer_state
{
	char		*input_copy;
	size_t		start;
	enum e_bool	is_word;
	enum e_bool	is_quoted;
}				t_lexer_state;

#endif
