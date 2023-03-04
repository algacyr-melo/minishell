/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:54:04 by almelo            #+#    #+#             */
/*   Updated: 2023/03/04 11:57:22 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	deep_free(char **envp)
//{
//	size_t	i;
//
//	i = 0;
//	while (envp[i])
//	{
//		free(envp[i]);
//		i++;
//	}
//	free(envp);
//}

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst)
{
	char	**argv;
	char	**envp;
	char	*pathname;
	pid_t	pid;

	argv = get_next_argv(token_lst);
	envp = list_to_envp(env_lst);
	pathname = get_pathname(argv, env_lst);
	pid = fork();
	if (pid == 0)
	{
		if (pathname)
		{
			if (execve(pathname, argv, envp) == -1)
				exit(0);
		}
		else
			exit(0);
	}
	else
		wait(&pid);
	//free(argv);
	//deep_free(envp);
}
