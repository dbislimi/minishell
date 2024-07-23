/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:00:30 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 16:24:54 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

// BUILTINS

void	set_signal_action(void);

// EXTENDER 

void	env_init(t_env **env, char **envp);
void	add_node(t_env **lst, t_env *newnode);
t_env	*last_node(t_env *lst);
t_env	*new_node(void *content);
void	envclear(t_env **lst);

#endif