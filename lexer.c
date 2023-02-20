/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:12 by almelo            #+#    #+#             */
/*   Updated: 2023/02/20 13:25:58 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_operator(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_metachar(int c)
{
	return (ft_isspace(c) || is_operator(c));
}

static enum e_label	get_label(int c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (IN);
	else if (c == '>')
		return (OUT);
	else
		return (WORD);
}

static enum e_bool	get_quote_state(int c, enum e_bool is_quoted)
{
	if ((c == '"' || c == '\'') && !is_quoted)
		is_quoted = TRUE;
	else if ((c == '"' || c == '\'') && is_quoted)
		is_quoted = FALSE;
	return (is_quoted);
}

// to do >> and << labels
void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state)
{
	size_t			i;

	token_lst->head = NULL;
	i = 0;
	while (i <= ft_strlen(input))
	{
		state->is_quoted = get_quote_state(input[i], state->is_quoted);
		if ((is_metachar(input[i]) || input[i] == '\0')
			&& (state->is_word && !state->is_quoted))
		{
			state->input_copy[i] = '\0';
			push_token(token_lst, new_token(state->input_copy + state->start, WORD));
			if (is_operator(input[i]))
				push_token(token_lst, new_token(NULL, get_label(input[i])));
			state->is_word = FALSE;
		}
		else if (is_operator(input[i]) && !state->is_word)
			push_token(token_lst, new_token(NULL, get_label(input[i])));
		if (!(is_metachar(input[i])) && !state->is_word && input[i] != '\0')
		{
			state->is_word = TRUE;
			state->start = i;
		}
		i++;
	}
}
