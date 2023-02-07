/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almelo <almelo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 23:23:55 by almelo            #+#    #+#             */
/*   Updated: 2023/02/07 15:49:59 by almelo           ###   ########.fr       */
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

void	set_signal_handler(void);

#endif
