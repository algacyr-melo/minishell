/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:04:31 by almelo            #+#    #+#             */
/*   Updated: 2023/03/29 17:46:56 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote_state(t_quote_state *state)
{
	state->prevent_default = FALSE;
	state->prevent_expand = FALSE;
}

void	update_quote_state(char *content, t_index *i, t_quote_state *state)
{
	if (content[i->old] == content[0])
	{
		if (state->prevent_default == FALSE)
			state->prevent_default = TRUE;
		else
			state->prevent_default = FALSE;
	}
	if (content[i->old] == '\'')
	{
		if (state->prevent_expand == FALSE)
			state->prevent_expand = TRUE;
		else
			state->prevent_expand = FALSE;
	}
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

void	copy_quote(char *new_content, char *content, t_index *i)
{
	new_content[i->new] = content[i->old];
	i->new++;
}
