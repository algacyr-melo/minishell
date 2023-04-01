/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:40:12 by almelo            #+#    #+#             */
/*   Updated: 2023/03/31 23:53:05 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

enum e_bool	get_state(char *input, int i, enum e_bool is_quoted, size_t *count)
{
	static char		quote;

	if (is_quote(input[i]))
	{
		if (!is_quoted)
		{
			quote = input[i];
			is_quoted = TRUE;
		}
		if (is_quoted && input[i] == quote)
			*count -= 1;
		if (*count == 0)
			is_quoted = FALSE;
		i++;
	}
	return (is_quoted);
}

static size_t	count_quote(char *input)
{
	size_t		counter;
	size_t		i;
	char		quote;
	enum e_bool	is_quoted;

	is_quoted = FALSE;
	counter = 0;
	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (!is_quoted)
			{
				quote = input[i];
				is_quoted = TRUE;
				counter++;
			}
			else if (is_quoted && input[i] == quote)
				counter++;
		}
		i++;
	}
	return (counter);
}

static void	update_state(t_lexer_state *state, size_t i)
{
	state->is_word = TRUE;
	state->curr = i;
}

void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state)
{
	size_t			i;
	static size_t	count;

	token_lst->head = NULL;
	count = count_quote(input);
	i = 0;
	while (i <= ft_strlen(input))
	{
		state->is_quoted = get_state(input, i, state->is_quoted, &count);
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
			update_state(state, i);
		i++;
	}
}
