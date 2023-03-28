/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/03/28 18:17:33 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_lexer_state(t_lexer_state *state, char *input_copy)
{
	state->input = input_copy;
	state->curr = 0;
	state->is_word = FALSE;
	state->is_quoted = FALSE;
}

void	handle_exit(t_envl *env_lst, int status)
{
	free_env_list(env_lst);
	printf("exit\n");
	exit(status);
}

int	is_quote(int c)
{
	return (c == '\"' || c == '\'');
}

void	update_parser_state(char *content, size_t i, t_parser_state *state)
{
	if (content[i] == content[0])
	{
		if (state->prevent_default == FALSE)
			state->prevent_default = TRUE;
		else
			state->prevent_default = FALSE;
	}
	if (content[i] == '\'')
	{
		if (state->prevent_expand == FALSE)
			state->prevent_expand = TRUE;
		else
			state->prevent_expand = FALSE;
	}
}

size_t	count_keys(char *content)
{
	size_t			len;
	size_t			i;
	t_parser_state	state;

	state.prevent_default = FALSE;
	state.prevent_expand = FALSE;
	len = 0;
	i = 0;
	while (content[i])
	{
		if (is_quote(content[i]))
			update_parser_state(content, i, &state);
		else if ((content[i] == '$')
			&& ((state.prevent_expand == FALSE)
				|| ((state.prevent_default && state.prevent_expand == TRUE)
					&& content[0] == '\"')))
			len++;
		i++;
	}
	return (len);
}

void	init_index(t_index *i)
{
	i->key = 0;
	i->new = 0;
	i->old = 0;
	i->start = 0;
}

void	handle_key(char *content, char **keys, t_index *i, enum e_bool *is_key)
{
	if (*is_key == FALSE)
		*is_key = TRUE;
	else if (*is_key == TRUE)
	{
		keys[i->key] = ft_substr(content, i->start, i->old - i->start);
		i->key++;
	}
	i->start = i->old + 1;
}

char	**get_keys(char *content)
{
	char		**key;
	size_t		key_counter;
	t_index		i;
	enum e_bool	is_key;

	key_counter = count_keys(content);
	key = malloc((key_counter + 1) * sizeof(*key));
	init_index(&i);
	is_key = FALSE;
	while (i.key < key_counter)
	{
		if (content[i.old] == '$')
			handle_key(content, key, &i, &is_key);
		else if (!ft_isalnum(content[i.old]) && is_key == TRUE)
		{
			key[i.key] = ft_substr(content, i.start, i.old - i.start);
			i.key++;
			is_key = FALSE;
		}
		i.old++;
	}
	key[i.key] = NULL;
	return (key);
}

size_t	parse_quote_count(char *content)
{
	size_t		count;
	size_t		i;
	enum e_bool	prevent_default;

	prevent_default = FALSE;
	count = 0;
	i = 0;
	while (content[i])
	{
		if (is_quote(content[i]))
		{
			if (content[i] == content[0])
			{
				if (prevent_default == FALSE)
					prevent_default = TRUE;
				else
					prevent_default = FALSE;
				count++;
			}
			else if (prevent_default == FALSE)
				count++;
		}
		i++;
	}
	return (count);
}

size_t	new_content_len(char *content, t_envl *env_lst, char **keys)
{
	size_t	len_new_content;
	size_t	len_value;
	size_t	len_key;
	t_env	*tmp;
	size_t	i;

	len_new_content = ft_strlen(content);
	i = 0;
	while (keys[i])
	{
		tmp = get_env(env_lst, keys[i]);
		if (tmp)
		{
			len_value = ft_strlen(tmp->value);
			len_key = ft_strlen(tmp->key);
			len_new_content += (len_value - len_key - 1);
		}
		i++;
	}
	len_new_content -= parse_quote_count(content);
	return (len_new_content);
}

void	ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

void	copy_quote(char *new_content, char *content, t_index *i)
{
	new_content[i->new] = content[i->old];
	i->new++;
}

void	copy_char(char *new_content, char *content, t_index *i)
{
	new_content[i->new] = content[i->old];
	i->new++;
	i->old++;
}

void	expand_variable(t_envl *env_lst, char *key, char *new, t_index *i)
{
	t_env	*tmp;

	tmp = get_env(env_lst, key);
	ft_strcpy(&new[i->new], tmp->value);
	i->old += ft_strlen(tmp->key) + 1;
	i->new += ft_strlen(tmp->value);
	i->key++;
}

void	init_parser_state(t_parser_state *state, char *content, t_envl *env_lst)
{
	state->prevent_default = FALSE;
	state->prevent_expand = FALSE;
	state->keys = get_keys(content);
	state->len_new = new_content_len(content, env_lst, state->keys);
	state->new = malloc((state->len_new + 1) * sizeof(char));
}

char	*parse_content(char *content, t_envl *env_lst)
{
	t_parser_state	state;
	t_index			i;

	init_parser_state(&state, content, env_lst);
	init_index(&i);
	while (i.new < state.len_new)
	{
		if (is_quote(content[i.old]))
		{
			update_parser_state(content, i.old, &state);
			if (state.prevent_default == TRUE && content[i.old] != content[0])
				copy_quote(state.new, content, &i);
			i.old++;
		}
		else if ((content[i.old] == '$')
			&& ((state.prevent_expand == FALSE)
				|| ((state.prevent_default && state.prevent_expand == TRUE)
					&& content[0] == '\"')))
			expand_variable(env_lst, state.keys[i.key], state.new, &i);
		else
			copy_char(state.new, content, &i);
	}
	state.new[i.new] = '\0';
	return (state.new);
}

void	parse_tokens(t_tokenl *token_lst, t_envl *env_lst)
{
	t_token		*tmp;

	tmp = token_lst->head;
	while (tmp)
	{
		if (tmp->label == WORD)
			tmp->content = parse_content(tmp->content, env_lst);
		tmp = tmp->next;
	}
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
		input = readline("minishell$ ");
		if (input == NULL)
			handle_exit(&env_lst, 0);
		add_history(input);
		init_lexer_state(&lexer_state, ft_strdup(input));
		tokenize_input(&token_lst, input, &lexer_state);
		parse_tokens(&token_lst, &env_lst);
		handle_execution(&token_lst, &env_lst);
		free(input);
		free(lexer_state.input);
	}
	return (0);
}
