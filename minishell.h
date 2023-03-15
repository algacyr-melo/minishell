/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:23:55 by almelo            #+#    #+#             */
/*   Updated: 2023/03/15 16:35:56 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>

# include <sys/types.h>
# include <sys/wait.h>

#include <errno.h>
#include <string.h>

# include "type.h"
# include "libft/header/libft.h"

void	set_signal_handler(void);

t_token	*new_token(void *content, enum e_label label);
void	queue_token(t_tokenl *token_lst, t_token *new);
t_token	*dequeue_token(t_tokenl *token_lst);

t_env	*new_env(void *key, void *value);
void	queue_env(t_envl *env_lst, t_env *new);

void	create_env_list(t_envl *env_lst, char **envp);
char	*get_key(char *env_str);
char	*get_value(char *env_str);

void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state);

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst);
char	**get_next_argv(t_tokenl *token_lst);
char	**list_to_envp(t_envl *env_lst);
char	*get_pathname(char **argv, t_envl *env_lst);
t_env	*get_env(t_envl *env_lst, char *key);

int		handle_builtin(char **argv, char **envp, t_envl *env_lst);
int		echo(int argc, char **argv);
int		cd(int argc, char **argv, t_envl *env_lst);
int		pwd(void);
int		ft_export(int argc, char **argv, char **envp, t_envl *env_lst);
int		unset(char **argv, t_envl *env_lst);
int		env(char **envp);
void	ft_exit(int argc, char **argv);

int		get_argc(char **argv);

void	free_token_list(t_tokenl *token_lst);
void	free_env_list(t_envl *env_lst);

#endif
