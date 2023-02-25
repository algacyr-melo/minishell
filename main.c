/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/02/24 21:27:39 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lexer_state(t_lexer_state *state, char *input_copy)
{
	state->input_copy = input_copy;
	state->start = 0;
	state->is_word = FALSE;
	state->is_quoted = FALSE;
}

void	free_env_list(t_envl *env_lst)
{
	t_env_node	*head;
	t_env_node	*tmp;

	head = env_lst->head;
	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_token_list(t_tokenl *token_lst)
{
	t_token	*head;
	t_token	*tmp;

	head = token_lst->head;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	handle_exit(t_envl *env_lst)
{
	free_env_list(env_lst);
	printf("exit\n");
	exit(0);
}

char	**list_to_array(t_tokenl *token_lst)
{
	char	**argv;
	t_token	*tmp;
	size_t	i;

	argv = malloc((token_lst->length + 1) * sizeof(char *));
	tmp = token_lst->head;
	i = 0;
	while (i < token_lst->length)
	{
		argv[i] = (char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*join_key_value(char *key, char *value)
{
	char	*content;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	content = malloc((key_len + value_len + 2) * sizeof(*content));
	ft_memcpy(content, key, key_len + 1);
	content[key_len] = '=';
	ft_memcpy(content + key_len + 1, value, value_len + 1);
	return (content);
}

char	**list_to_envp(t_envl *env_lst)
{
	char		**envp;
	t_env_node	*tmp;
	size_t		i;

	envp = malloc((env_lst->length + 1) * sizeof(char *));
	tmp = env_lst->head;
	i = 0;
	while (i < env_lst->length)
	{
		envp[i] = join_key_value(tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_pathname(char **argv, t_envl *env_lst)
{
	char	**pathv;
	char	*pathname;
	size_t	i;

	if (access(argv[0], F_OK) == 0)
		return (argv[0]);
	pathv = ft_split(env_lst->path->value, ':');
	argv[0] = ft_strjoin("/", argv[0]);
	i = 0;
	while (pathv[i])
	{
		pathname = ft_strjoin(pathv[i], argv[0]);
		if (access(pathname, F_OK) == 0)
			return (pathname);
		i++;
	}
	return (NULL);
}

void	deep_free(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst)
{
	char	**argv;
	char	**envp;
	char	*pathname;
	pid_t	pid;

	argv = list_to_array(token_lst);
	envp = list_to_envp(env_lst);
	pid = fork();
	if (pid == 0)
	{
		pathname = get_pathname(argv, env_lst);
		if (pathname)
		{
			if (execve(pathname, argv, envp) == -1)
				exit(0);
		}
		else
		{
			free(argv);
			deep_free(envp);
			exit(0);
		}
	}
	else
		wait(&pid);
	free(argv);
	deep_free(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_envl			env_lst;
	t_tokenl		token_lst;
	t_lexer_state	lexer_state;

	(void)argc;
	(void)argv;
	set_signal_handler();
	create_env_list(&env_lst, envp);
	while (42)
	{
		input = readline("minishell> ");
		if (input == NULL)
			handle_exit(&env_lst);
		add_history(input);
		init_lexer_state(&lexer_state, ft_strdup(input));
		tokenize_input(&token_lst, input, &lexer_state);
		handle_execution(&token_lst, &env_lst);
		free(input);
		free(lexer_state.input_copy);
		free_token_list(&token_lst);
	}
	return (0);
}
