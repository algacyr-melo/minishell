/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:56:07 by almelo            #+#    #+#             */
/*   Updated: 2023/03/09 12:07:51 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(char **argv, t_envl *env_lst)
{
	char    *key;
	char    *value;
	t_env   *tmp;

	key = get_key(argv[1]);
	value = get_value(argv[1]);
	if (key == NULL || value == NULL)
		return (1);
	tmp = get_env(env_lst, key);
	if (tmp)
		tmp->value = value;
	else
		queue_env(env_lst, new_env(key, value));
	return (0);
}
