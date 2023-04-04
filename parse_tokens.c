/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:14:05 by almelo            #+#    #+#             */
/*   Updated: 2023/04/03 21:11:01 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_keys(char **keys)
{
	size_t	i;

	i = 0;
	while (keys[i])
	{
		free(keys[i]);
		i++;
	}
	free(keys);
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
	free_keys(state.keys);
	state.new[i.new] = '\0';
	return (state.new);
}

int	handle_append_syntax(t_token *curr, t_token *prev)
{
	if (prev == NULL || curr->next->next == NULL
			|| curr->next->label != WORD || prev->label != WORD)
	{
		printf("minishell: syntax error near unexpected token `>>'\n");
		return (2);
	}
	return (0);
}

int	handle_heredoc_syntax(t_token *curr, t_token *prev)
{
	if (prev == NULL || curr->next->next == NULL
			|| curr->next->next->label != WORD || prev->label != WORD)
	{
		printf("minishell: syntax error near unexpected token `<<'\n");
		return (2);
	}
	return (0);
}

int	check_syntax(t_tokenl *token_lst)
{
	t_token	*curr;
	t_token	*prev;

	prev = NULL;
	curr = token_lst->head;
	while (curr)
	{
		if (curr->label == PIPE || curr->label == IN || curr->label == OUT)
		{
			if (prev == NULL || curr->next == NULL 
					|| curr->next->label != WORD
					|| prev->label != WORD)
			{
				printf("minishell: syntax error\n");
				return (2);
			}
		}
		else if (curr->label == APPEND)
			return (handle_append_syntax(curr, prev));
		else if (curr->label == HEREDOC)
			return (handle_heredoc_syntax(curr, prev));
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	parse_tokens(t_tokenl *token_lst, t_envl *env_lst)
{
	t_token	*tmp;

	g_exit_status = check_syntax(token_lst);
	if (g_exit_status != 0)
		return (1);
	tmp = token_lst->head;
	while (tmp)
	{
		if (tmp->label == WORD)
			tmp->content = parse_content(tmp->content, env_lst);
		tmp = tmp->next;
	}
	return (0);
}
