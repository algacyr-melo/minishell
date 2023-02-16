/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/16 15:30:49 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static t_token	*new_token(void *content)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->content = content;
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

static int	is_null(int c)
{
	return (c == '\0');
}

void	tokenize_input(t_tokenl *token_lst, char *input)
{
	size_t			start;
	size_t			i;
	char			*content;
	//enum e_label	label;
	enum e_bool		is_reading;
	enum e_bool		is_quoted;

	token_lst->head = NULL;
	is_reading = FALSE;
	is_quoted = FALSE;
	start = 0;
	i = 0;
	while (input[i] || is_reading == TRUE)
	{
		// update quote status
		if (input[i] == '"' && !is_quoted)
			is_quoted = TRUE;
		else if (input[i] == '"' && is_quoted)
			is_quoted = FALSE;
		if ((is_space(input[i]) || is_null(input[i])) && (is_reading && !is_quoted))
		{
			// handle tokenize
			*(input + i) = '\0';
			content = ft_strdup(input + start);
			//label = get_label(input[i]);
			push_token(token_lst, new_token(content));
			is_reading = FALSE;
		}
		// update reading status
		else if (!(is_space(*(input + i))) && !is_reading && !is_null(*(input + i)))
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
			printf("%s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		add_history(input);
		free(input);
	}
	free(input);
	return (0);
}
