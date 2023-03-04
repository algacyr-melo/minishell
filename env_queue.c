/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:20:09 by almelo            #+#    #+#             */
/*   Updated: 2023/03/04 14:21:02 by almelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 t_env   *new_env(void *key, void *value)
 {
     t_env   *node;
 
     node = malloc(sizeof(t_env));
     node->key = key;
     node->value = value;
     node->next = NULL;
     return (node);
 }
 
 void    queue_env(t_envl *env_lst, t_env *new)
 {
     if (env_lst->head == NULL)
     {
         env_lst->head = new;
         env_lst->tail = new;
     }
     else
     {
         env_lst->tail->next = new;
         env_lst->tail = new;
     }
     if (ft_strcmp(new->key, "PATH") == 0)
         env_lst->path = new;
     env_lst->length++;
 }
