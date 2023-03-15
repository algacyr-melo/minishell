/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:45:47 by almelo            #+#    #+#             */
/*   Updated: 2023/03/15 18:20:02 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(int argc, char **argv)
{
    size_t      i;
    enum e_bool end_nl;

    end_nl = TRUE;
    if (argc > 1)
    {
        i = 1;
        if (ft_strcmp(argv[i], "-n") == 0)
        {
            end_nl = FALSE;
            i++;
        }
        while (argv[i])
        {
            ft_putstr_fd(argv[i], STDOUT_FILENO);
			if (argv[i + 1])
            	ft_putchar_fd(' ', STDOUT_FILENO);
            i++;
        }
    }
    if (end_nl == TRUE)
        ft_putchar_fd('\n', STDOUT_FILENO);
    exit(0);
}
