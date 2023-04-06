/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:23:55 by almelo            #+#    #+#             */
/*   Updated: 2023/04/06 14:41:35 by almelo           ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>

# include <errno.h>
# include <string.h>

# include "type.h"
# include "libft/header/libft.h"

extern int	g_exit_status;

void	set_signal_handler_parent(void);
void	set_signal_handler_child(void);

t_token	*new_token(void *content, enum e_label label);
void	queue_token(t_tokenl *token_lst, t_token *new);
t_token	*dequeue_token(t_tokenl *token_lst);

t_env	*new_env(void *key, void *value);
void	queue_env(t_envl *env_lst, t_env *new);

void	create_env_list(t_envl *env_lst, char **envp);
char	*get_key(char *env_str);
char	*get_value(char *env_str);

void	tokenize_input(t_tokenl *token_lst, char *input, t_lexer_state *state);

int		check_syntax(t_tokenl *token_lst);
int		parse_tokens(t_tokenl *token_lst, t_envl *env_lst);
char	*parse_content(char *content, t_envl *env_lst);
void	init_parser_state(t_parser_state *state, char *content, t_envl *envlst);
void	update_parser_state(char *content, size_t i, t_parser_state *state);
size_t	count_keys(char *content);

size_t	parse_quote_count(char *content);
void	init_quote_state(t_quote_state *state);
void	update_quote_state(char *content, t_index *i, t_quote_state *state);
void	expand_variable(t_envl *env_lst, char *key, char *new, t_index *i);

int		handle_redirect(t_tokenl *token_lst, int *prevpipe);
void	handle_heredoc(t_tokenl *token_lst, int prevpipe);
void	ft_pipe(char **argv, char **envp, t_envl *env_lst, int *prevpipe);
void	ft_last(char **argv, char **envp, t_envl *env_lst, int *prevpipe);

void	handle_execution(t_tokenl *token_lst, t_envl *env_lst);
void	try_execute(char **argv, char **envp, t_envl *env_lst);
char	**get_next_argv(t_tokenl *token_lst);
char	**list_to_envp(t_envl *env_lst);
char	*get_pathname(char **argv, t_envl *env_lst);
t_env	*get_env(t_envl *env_lst, char *key);

t_envl	*handle_builtin_pp(char **argv, char **envp, t_envl *env_lst);
int		handle_builtin_cp(char **argv, char **envp);
void	echo(int argc, char **argv);
int		cd(int argc, char **argv, t_envl *env_lst);
void	pwd(void);
int		ft_export(int argc, char **argv, char **envp, t_envl *env_lst);
int		unset(char **argv, t_envl *env_lst);
void	env(char **envp);
void	ft_exit(int argc, char **argv);

int		get_argc(char **argv);

void	free_token_list(t_tokenl *token_lst);
void	free_env_list(t_envl *env_lst);

int		is_quote(int c);
int		is_operator(int c);
int		is_metachar(int c);
void	init_index(t_index *i);
void	copy_quote(char *new, char *content, t_index *i);
void	copy_char(char *new, char *content, t_index *i);
void	ft_strcpy(char *dst, char *src);
void	handle_key(char *content, char **key, t_index *i, enum e_bool *is_key);
void	save_switch(char *content, char **key, t_index *i, enum e_bool *is_key);

#endif
