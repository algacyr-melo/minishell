/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:43:30 by almelo            #+#    #+#             */
/*   Updated: 2023/02/25 16:21:32 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int signo)
{
	(void)signo;
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
	sigint_act.sa_flags = SA_RESTART;
	sigemptyset(&sigint_act.sa_mask);
	sigaction(SIGINT, &sigint_act, NULL);
	sigquit_act.sa_handler = SIG_IGN;
	sigquit_act.sa_flags = SA_RESTART;
	sigemptyset(&sigquit_act.sa_mask);
	sigaction(SIGQUIT, &sigquit_act, NULL);
}
