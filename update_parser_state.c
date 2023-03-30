/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_parser_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:45:42 by almelo            #+#    #+#             */
/*   Updated: 2023/03/29 23:04:34 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
