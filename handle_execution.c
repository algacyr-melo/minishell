/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:54:04 by almelo            #+#    #+#             */
/*   Updated: 2023/03/07 00:39:30 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(int argc, char **argv)
{
	size_t		i;
	enum e_bool	end_nl;

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
			ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (end_nl == TRUE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

int	cd(int argc, char **argv, t_envl *env_lst)
{
	char	*path;

	if (argc == 1)
		path = env_lst->home->value;
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: %s\n", argv[1], strerror(errno));
		return (errno);
	}
	return (0);
}

int	pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
	return (0);
}

int	export(char **argv, t_envl *env_lst)
{
	char	*key;
	char	*value;

	//to do: if already exists, replace it
	key = get_key(argv[1]);
	if (!key)
		return (1);
	value = get_value(argv[1]);
	queue_env(env_lst, new_env(key, value));
	return (0);
}

static t_env	*remove_env(t_envl *env_lst, char *key)
{
	t_env	*tmp;
	t_env	*node;

	tmp = env_lst->head;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->next->key, key) == 0)
		{
			node = tmp->next;
			tmp->next = tmp->next->next;
			return (node);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	unset(char **argv, t_envl *env_lst)
{
	char	*key;
	t_env	*tmp;

	key = get_key(argv[1]);
	tmp = remove_env(env_lst, key);
	free(tmp);
	return (0);
}

int	env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	is_numeric_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(int argc, char **argv)
{
	int	n;

	n = 0;
	if (argc == 2 && is_numeric_arg(argv[1]))
		n = ft_atoi(argv[1]);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(n);
}

int	get_argc(char **argv)
{
	size_t	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

int	handle_builtin(char **argv, char **envp, t_envl *env_lst)
{
	int	argc;

	argc = get_argc(argv);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(argc, argv));
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argc, argv, env_lst));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(argv[0], "export") == 0)
		return (export(argv, env_lst));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(argv, env_lst));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (env(envp));
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(argc, argv);
	return (-1);
}

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst)
{
	char	**argv;
	char	**envp;
	char	*pathname;
	pid_t	pid;

	envp = list_to_envp(env_lst);
	argv = get_next_argv(token_lst);
	if (handle_builtin(argv, envp, env_lst) == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			pathname = get_pathname(argv, env_lst);
			if (execve(pathname, argv, envp) == -1)
				exit(0);
		}
		else
			wait(&pid);
	}
}
