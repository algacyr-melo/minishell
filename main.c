/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/10 23:02:45 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	len;
	int		i;

	len = ft_strlen(str);
	dup = malloc((len + 1) * sizeof(char));
	i = 0;
	while (*(str + i))
	{
		*(dup + i) = *(str + i);
		i++;
	}
	*(dup + i) = '\0';
	return (dup);
}

char	**envp_dup(char **envp)
{
	char	**dup;
	size_t	len;
	size_t	i;

	len = 0;
	while (*(envp + len))
		len++;
	dup = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		*(dup + i) = ft_strdup(*(envp + i));
		i++;
	}
	*(dup + i) = NULL;
	return (dup);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**envp_copy;

	(void)argc;
	(void)argv;
	set_signal_handler();
	envp_copy = envp_dup(envp);
	(void)envp_copy;
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
