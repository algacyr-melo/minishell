/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/19 13:32:12 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lexer_state(t_lexer_state *state, char *input)
{
	state->input_copy = input;
	state->start = 0;
	state->is_word = FALSE;
	state->is_quoted = FALSE;
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
