/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/03/29 22:52:15 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lexer_state(t_lexer_state *state, char *input_copy)
{
	state->input = input_copy;
	state->curr = 0;
	state->is_word = FALSE;
	state->is_quoted = FALSE;
}

void	handle_exit(t_envl *env_lst, int status)
{
	free_env_list(env_lst);
	printf("exit\n");
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_envl			env_lst;
	t_tokenl		token_lst;
	t_lexer_state	lexer_state;

	(void)argc;
	(void)argv;
	set_signal_handler();
	create_env_list(&env_lst, envp);
	while (42)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			handle_exit(&env_lst, 0);
		add_history(input);
		init_lexer_state(&lexer_state, ft_strdup(input));
		tokenize_input(&token_lst, input, &lexer_state);
		parse_tokens(&token_lst, &env_lst);
		handle_execution(&token_lst, &env_lst);
		free(input);
		free(lexer_state.input);
	}
	return (0);
}
