/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:23:55 by almelo            #+#    #+#             */
/*   Updated: 2023/02/25 16:09:09 by almelo           ###   ########.fr       */
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

void	create_env_list(t_envl *env_lst, char **envp);

void	push_token(t_tokenl *token_lst, t_token *new);
t_token	*new_token(void *content, enum e_label label);

void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state);

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst);
char	**list_to_array(t_tokenl *token_lst);
char	**list_to_envp(t_envl *env_lst);
char	*get_pathname(char **argv, t_envl *env_lst);

void	free_token_list(t_tokenl *token_lst);
void	free_env_list(t_envl *env_lst);

#endif
