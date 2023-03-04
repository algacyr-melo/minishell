/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:23:55 by almelo            #+#    #+#             */
/*   Updated: 2023/03/04 14:06:02 by almelo           ###   ########.fr       */
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

# include "type.h"
# include "libft/header/libft.h"

void	set_signal_handler(void);

t_token	*new_token(void *content, enum e_label label);
void	queue_token(t_tokenl *token_lst, t_token *new);
t_token	*dequeue_token(t_tokenl *token_lst);

t_env	*new_env(void *key, void *value);
void	queue_env(t_envl *env_lst, t_env *new);

void	create_env_list(t_envl *env_lst, char **envp);

void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state);

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst);
char	**get_next_argv(t_tokenl *token_lst);
char	**list_to_envp(t_envl *env_lst);
char	*get_pathname(char **argv, t_envl *env_lst);

void	free_token_list(t_tokenl *token_lst);
void	free_env_list(t_envl *env_lst);

#endif
