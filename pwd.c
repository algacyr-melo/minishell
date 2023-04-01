/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:53:30 by almelo            #+#    #+#             */
/*   Updated: 2023/03/20 22:21:01 by dioda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		exit(errno);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
	exit(0);
}
