/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/17 02:25:39 by almelo           ###   ########.fr       */
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

void	tokenize_input(t_tokenl *token_lst, char *input)
{
	size_t			start;
	size_t			i;
	char			*content;
	enum e_bool		is_reading;
	enum e_bool		is_quoted;
	int				tmp;

	token_lst->head = NULL;
	is_reading = FALSE;
	is_quoted = FALSE;
	start = 0;
	i = 0;
	while (input[i] || is_reading == TRUE)
	{
		// update quote status
		if ((input[i] == '"' || input[i] == '\'') && !is_quoted)
			is_quoted = TRUE;
		else if ((input[i] == '"' || input[i] == '\'') && is_quoted)
			is_quoted = FALSE;
		if ((is_metachar(input[i]) || input[i] == '\0') && (is_reading && !is_quoted))
		{
			// handle tokenize
			tmp = input[i];
			input[i] = '\0';
			content = ft_strdup(input + start);
			push_token(token_lst, new_token(content, WORD));
			if (is_operator(tmp))
				push_token(token_lst, new_token(NULL, get_label(tmp)));
			is_reading = FALSE;
		}
		else if (is_operator(input[i]) && !is_reading)
			push_token(token_lst, new_token(NULL, get_label(input[i])));
		// update reading status
		if (!(is_metachar(input[i])) && !is_reading && input[i] != '\0')
		{
			is_reading = TRUE;
			start = i;
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
		tokenize_input(&token_lst, input);
		tmp = token_lst.head;
		while (tmp)
		{
			printf("%s: %d\n", (char *)tmp->content, tmp->label);
			tmp = tmp->next;
		}
		add_history(input);
		free(input);
	}
	free(input);
	return (0);
}
