/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/19 12:00:18 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static t_token	*new_token(void *content, enum e_label label)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->content = content;
	token->label = label;
	token->next = NULL;
	return (token);
}

static void	push_token(t_tokenl *token_lst, t_token *new)
{
	if (token_lst->head == NULL)
		token_lst->head = new;
	else
	{
		new->next = token_lst->head;
		token_lst->head = new;
	}
}

static int	is_operator(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_metachar(int c)
{
	return (is_space(c) || is_operator(c));
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

void	init_lexer_state(t_lexer_state *state, char *input)
{
	state->input_copy = input;
	state->start = 0;
	state->is_word = FALSE;
	state->is_quoted = FALSE;
}

enum e_bool	get_quote_state(int c, enum e_bool is_quoted)
{
	if ((c == '"' || c == '\'') && !is_quoted)
		is_quoted = TRUE;
	else if ((c == '"' || c == '\'') && is_quoted)
		is_quoted = FALSE;
	return (is_quoted);
}

void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state)
{
	size_t			i;

	token_lst->head = NULL;
	i = 0;
	while (input[i] != '\0' || state->is_word == TRUE)
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

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_envl			env_lst;
	t_tokenl		token_lst;
	t_token			*tmp;
	t_lexer_state	lexer_state;

	(void)argc;
	(void)argv;
	set_signal_handler();
	create_env_list(&env_lst, envp);
	while (42)
	{
		input = readline("minishell> ");
		if (input == NULL)
			exit(0);
		add_history(input);
		init_lexer_state(&lexer_state, ft_strdup(input));
		tokenize_input(&token_lst, input, &lexer_state);
		tmp = token_lst.head;
		while (tmp)
		{
			printf("%s: %d\n", (char *)tmp->content, tmp->label);
			tmp = tmp->next;
		}
		free(input);
	}
	return (0);
}
