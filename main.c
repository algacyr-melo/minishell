/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/19 10:46:28 by almelo           ###   ########.fr       */
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
	state->input = input;
	state->start = 0;
	state->is_word = FALSE;
	state->is_quoted = FALSE;
}

void	tokenize_input(t_tokenl *token_lst, char *input)
{
	t_lexer_state	state;
	size_t			i;
	int				tmp;

	init_lexer_state(&state, input);
	token_lst->head = NULL;
	i = 0;
	while (input[i] || state.is_word == TRUE)
	{
		// update quote status
		if ((input[i] == '"' || input[i] == '\'') && !state.is_quoted)
			state.is_quoted = TRUE;
		else if ((input[i] == '"' || input[i] == '\'') && state.is_quoted)
			state.is_quoted = FALSE;
		if ((is_metachar(input[i]) || input[i] == '\0')
			&& (state.is_word && !state.is_quoted))
		{
			// handle tokenize
			tmp = input[i];
			input[i] = '\0';
			push_token(token_lst, new_token(input + state.start, WORD));
			if (is_operator(tmp))
				push_token(token_lst, new_token(NULL, get_label(tmp)));
			state.is_word = FALSE;
		}
		else if (is_operator(input[i]) && !state.is_word)
			push_token(token_lst, new_token(NULL, get_label(input[i])));
		// update reading status
		if (!(is_metachar(input[i])) && !state.is_word && input[i] != '\0')
		{
			state.is_word = TRUE;
			state.start = i;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_envl		env_lst;
	t_tokenl	token_lst;
	t_token		*tmp;

	(void)argc;
	(void)argv;
	set_signal_handler();
	create_env_list(&env_lst, envp);
	while (42)
	{
		input = readline("minishell> ");
		if (input == NULL)
			exit(0);
		if (strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		tokenize_input(&token_lst, input);
		tmp = token_lst.head;
		while (tmp)
		{
			printf("%s: %d\n", (char *)tmp->content, tmp->label);
			tmp = tmp->next;
		}
		free(input);
	}
	free(input);
	return (0);
}
