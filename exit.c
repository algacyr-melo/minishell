/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:08:10 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 18:09:09 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_numeric_arg(char *arg)
{
	size_t  i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void    ft_exit(int argc, char **argv)
{
	int n;

	n = 0;
	if (argc == 2 && is_numeric_arg(argv[1]))
		n = ft_atoi(argv[1]);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(n);
}
