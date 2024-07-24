/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:00:30 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 20:09:45 by dbislimi         ###   ########.fr       */
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
# include <stdbool.h>


// BUILTINS

void	set_signal_action(void);

// EXTENDER 

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

void	env_init(t_env **env, char **envp);
void	add_node(t_env **lst, t_env *newnode);
t_env	*new_node(void *content);
void	envclear(t_env **lst);

// LEXER

typedef struct s_lexer
{
	char	*content;
	int		token;
}		t_lexer;

typedef struct s_flag
{
	bool	sg_quote;
	bool	d_quote;
}		t_flag;

typedef struct s_index
{
	int	start;
	int	end;
}	t_index;

void	lexing(char *str);
t_lexer	*new_nodefl(void *content);

#endif