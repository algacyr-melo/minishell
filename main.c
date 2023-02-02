/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/01 23:19:25 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	*input;

	while (42)
	{
		input = readline("minishell> ");
		if (strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		free(input);
	}
	free(input);
	return (0);
}
