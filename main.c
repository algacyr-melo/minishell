/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/13 23:43:48 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	print_env_list(t_node *head)
//{
//	t_node	*tmp;
//
//	tmp = head;
//	while (tmp)
//	{
//		printf("%s=%s\n", (char *)tmp->key, (char *)tmp->value);
//		tmp = tmp->next;
//	}
//}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_envl	env_lst;

	(void)argc;
	(void)argv;
	set_signal_handler();
	create_env_list(&env_lst, envp);
	//print_env_list(env_lst.head);
	while (42)
	{
		input = readline("minishell> ");
		if (input == NULL)
			exit(0);
		if (strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		free(input);
	}
	free(input);
	return (0);
}
