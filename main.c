/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/11 19:11:56 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(void *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->value = value;
	node->next = NULL;
	return (node);
}

void	push(t_envl *env_lst, t_node *new)
{
	if (env_lst->head == NULL)
		env_lst->head = new;
	else
	{
		new->next = env_lst->head;
		env_lst->head = new;
	}
}

void	create_env_list(t_envl *env_lst, char **envp)
{
	size_t	i;

	env_lst->head = NULL;
	i = 0;
	while (*(envp + i))
	{
		push(env_lst, new_node(envp[i])); 
		i++;
	}
}

void	print_env_list(t_node *head)
{
	t_node	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->value);
		tmp = tmp->next;
	}
}

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
