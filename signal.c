/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:43:30 by almelo            #+#    #+#             */
/*   Updated: 2023/04/06 00:00:28 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler_parent(int signo)
{
	(void)signo;
	if (g_exit_status == 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
	}
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal_handler_parent(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	sigint_act.sa_handler = sigint_handler_parent;
	sigint_act.sa_flags = 0;
	sigemptyset(&sigint_act.sa_mask);
	sigaction(SIGINT, &sigint_act, NULL);
	sigquit_act.sa_handler = SIG_IGN;
	sigquit_act.sa_flags = 0;
	sigemptyset(&sigquit_act.sa_mask);
	sigaction(SIGQUIT, &sigquit_act, NULL);
}

//static void	sigint_handler_child(int signo)
//{
//	(void)signo;
//	//ft_putchar_fd('\0', STDOUT_FILENO);
//	//rl_replace_line("", 1);
//	//rl_redisplay();
//	exit(130);
//}

void	set_signal_handler_child(void)
{
	struct sigaction	sigint_act;
	struct sigaction	sigquit_act;

	//sigint_act.sa_handler = sigint_handler_child;
	sigint_act.sa_handler = SIG_DFL;
	sigint_act.sa_flags = 0;
	sigemptyset(&sigint_act.sa_mask);
	sigaction(SIGINT, &sigint_act, NULL);

	sigquit_act.sa_handler = SIG_IGN;
	sigquit_act.sa_flags = 0; 
	sigemptyset(&sigquit_act.sa_mask);
	sigaction(SIGQUIT, &sigquit_act, NULL);
}
