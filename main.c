/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:15:15 by almelo            #+#    #+#             */
/*   Updated: 2023/03/22 21:09:45 by almelo           ###   ########.fr       */
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

size_t	keys_len(char *content)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
			len++;
		i++;
	}
	return (len);
}

char	**get_keys(char *content)
{
	char		**keys;
	size_t		start;
	size_t		i;
	size_t		i_keys;
	size_t		len;
	enum e_bool	is_key;

	len = keys_len(content);
	keys = malloc((len + 1) * sizeof(*keys));
	start = 0;
	i = 0;
	i_keys = 0;
	is_key = FALSE;
	while (i_keys < len)
	{
		if (content[i] == '$')
		{
			if (is_key == FALSE)
				is_key = TRUE;
			else if (is_key == TRUE)
			{
				keys[i_keys] = ft_substr(content, start, i - start);
				i_keys++;
			}
			start = i + 1;
		}
		else if (!ft_isalnum(content[i]) && is_key == TRUE)
		{
			keys[i_keys] = ft_substr(content, start, i - start);
			i_keys++;
			is_key = FALSE;
		}
		i++;
	}
	keys[i_keys] = NULL;
	return (keys);
}

int	is_quote(int c)
{
	return (c == '\"' || c == '\'');
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

char	*parse_content(char *content, t_envl *env_lst)
{
	char		**keys;
	char		*new_content;
	size_t		len_new_content;
	size_t		i;
	size_t		i_keys;
	size_t		i_new;
	t_env		*tmp;
	enum e_bool	prevent_default;

	prevent_default = FALSE;
	keys = get_keys(content);
	len_new_content = new_content_len(content, env_lst, keys);
	new_content = malloc((len_new_content + 1) * sizeof(*new_content));
	i_keys = 0;
	i_new = 0;
	i = 0;
	while (i_new < len_new_content)
	{
		if (content[i] == '$' && get_env(env_lst, keys[i_keys]))
		{
			tmp = get_env(env_lst, keys[i_keys]);
			ft_strcpy(&new_content[i_new], tmp->value);
			i += ft_strlen(tmp->key) + 1;
			i_new += ft_strlen(tmp->value);
			i_keys++;
		}
		else if (is_quote(content[i]))
		{
			if (content[i] == content[0])
			{
				if (prevent_default == FALSE)
					prevent_default = TRUE;
				else
					prevent_default = FALSE;
			}
			else if (prevent_default == TRUE)
			{
				new_content[i_new] = content[i];
				i_new++;
			}
			i++;
		}
		else
		{
			new_content[i_new] = content[i];
			i_new++;
			i++;
		}
	}
	new_content[i_new] = '\0';
	return (new_content);
}

static int	str_quote(char *content)
{
	return (ft_strchr(content, '\'')
		|| ft_strchr(content, '\"'));
}

void	parse_tokens(t_tokenl *token_lst, t_envl *env_lst)
{
	t_token		*tmp;

	(void)env_lst;
	tmp = token_lst->head;
	while (tmp)
	{
		if (tmp->label == WORD
			&& (str_quote(tmp->content) || ft_strchr(tmp->content, '$')))
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
