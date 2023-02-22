/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/22 16:47:06 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lexer_state(t_lexer_state *state, char *input_copy)
{
	state->input_copy = input_copy;
	state->start = 0;
	state->is_word = FALSE;
	state->is_quoted = FALSE;
}

void	free_env_list(t_envl *env_lst)
{
	t_env_node	*head;
	t_env_node	*tmp;

	head = env_lst->head;
	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_token_list(t_tokenl *token_lst)
{
	t_token	*head;
	t_token	*tmp;

	head = token_lst->head;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	handle_exit(t_envl *env_lst)
{
	free_env_list(env_lst);
	printf("exit\n");
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_envl			env_lst;
	t_tokenl		token_lst;
	t_lexer_state	lexer_state;
	t_token			*tmp;

	(void)argc;
	(void)argv;
	set_signal_handler();
	create_env_list(&env_lst, envp);
	while (42)
	{
		input = readline("minishell> ");
		if (input == NULL)
			handle_exit(&env_lst);
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
		free(lexer_state.input_copy);
		free_token_list(&token_lst);
	}
	return (0);
}
