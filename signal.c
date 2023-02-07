/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:43:30 by almelo            #+#    #+#             */
/*   Updated: 2023/02/07 15:54:06 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, 1);
}

static void	sigint_handler()
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal_handler(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	sigint_act.sa_handler = sigint_handler;
	sigaction(SIGINT, &sigint_act, NULL);

	sigquit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigquit_act, NULL);
}
