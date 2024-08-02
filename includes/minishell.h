/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:00:30 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/02 19:42:00 by dbislimi         ###   ########.fr       */
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

typedef enum token
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPENDOUTPUT
}	t_token;

typedef struct s_lexer
{
	char			*content;
	t_token			token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}		t_lexer;

typedef struct s_flag
{
	bool	sg_quote;
	bool	d_quote;
	int		backslash;
}		t_flag;

typedef struct s_index
{
	int	start;
	int	end;
}	t_index;


t_lexer	*lexer(t_lexer *list, char *str, t_env *env);
char	**ft_split_lexer(char *s);
int		count_words_lexer(char *s);
void	handle_quotes(char c, int *res, t_flag *flag);
void	is_start_of_word(int *res, t_flag f, bool *flag);
void	found_quote(t_index *idx, const char *s, bool *flag);
void	found_word(t_index *idx, const char *s, bool *flag);
t_lexer	*lexer_init(t_lexer **lexer, char **split, t_env *env);
char	*clean_str(char *str, t_env *env);
char	*find_value(char *str, t_env *env);
size_t	handle_dollar(char *clean, char **tab, char *env_value);
size_t	count_dollar(char *str, t_env *env);
void	free_lexer(t_lexer **lexer);
void	print_lexer(t_lexer *lexer);
void	handle_backslash(char c, int *backslash);
t_lexer	*delete_empty_nodes(t_lexer *lexer);

//PARSER

typedef struct s_parser
{
	char	**str;
	t_lexer	*redirections;
	struct s_parser	*next;
	struct s_parser	*prev;	
}		t_parser;

#endif