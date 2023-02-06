/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/06 00:00:17 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, 1);
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(void)
{
	char				*input;
	struct sigaction	act;

	while (42)
	{
		act.sa_handler = signal_handler;
		sigaction(SIGINT, &act, NULL);
		input = readline("minishell> ");
		if (strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		free(input);
	}
	free(input);
	return (0);
}
