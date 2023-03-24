/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:12 by almelo            #+#    #+#             */
/*   Updated: 2023/03/24 14:30:14 by almelo           ###   ########.fr       */
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

static enum e_label	get_label(char *input, size_t i)
{
	if (input[i] == '|')
		return (PIPE);
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (HEREDOC);
		else
			return (IN);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (APPEND);
		else
			return (OUT);
	}
	else
		return (WORD);
}

static enum e_bool	get_quote_state(char *input, int i, enum e_bool is_quoted)
{
	static char	quote;

	if ((input[i] == '\"' || input[i] == '\'') && !is_quoted)
	{
		quote = input[i];
		is_quoted = TRUE;
	}
	else if (input[i] == quote && is_quoted)
		is_quoted = FALSE;
	return (is_quoted);
}

void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state)
{
	size_t			i;

	token_lst->head = NULL;
	i = 0;
	while (i <= ft_strlen(input))
	{
		state->is_quoted = get_quote_state(input, i, state->is_quoted);
		if ((is_metachar(input[i]) || input[i] == '\0')
			&& (state->is_word && !state->is_quoted))
		{
			state->input[i] = '\0';
			queue_token(token_lst, new_token(state->input + state->curr, WORD));
			if (is_operator(input[i]))
				queue_token(token_lst, new_token(NULL, get_label(input, i)));
			state->is_word = FALSE;
		}
		else if (is_operator(input[i]) && !state->is_word)
			queue_token(token_lst, new_token(NULL, get_label(input, i)));
		if (!(is_metachar(input[i])) && !state->is_word && input[i] != '\0')
		{
			state->is_word = TRUE;
			state->curr = i;
		}
		i++;
	}
}
