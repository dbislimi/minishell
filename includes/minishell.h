/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:00:30 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/14 13:19:37 by dbislimi         ###   ########.fr       */
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

# define SYNTAX_ERROR "minishell: syntax error near unexpected token"

// EXTENDER 

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

void	env_init(t_env **env, char **envp);
int		env_edit(t_env **lst, t_env *newnode);
void	add_node(t_env **lst, t_env *newnode);
t_env	*new_node(void *content);
void	envclear(t_env **lst);
void	print_env(t_env *env, char *type);
void	print_export(t_env *env, int i);
void	print_brut_format(char c);

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

void	lexer(t_lexer **list, char *str, t_env *env);
char	**ft_split_lexer(char *s);
int		count_words_lexer(char *s);
int		handle_quotes(char c, t_flag *flag);
void	is_start_of_word(int *res, t_flag f, bool *flag);
void	found_quote(t_index *idx, const char *s, bool *flag);
void	found_word(t_index *idx, const char *s, bool *flag);
void	lexer_init(t_lexer **lexer, char **split, t_env *env);
t_lexer	*new_node_lexer(char *content, t_token tk, int i);
void	add_node_lexer(t_lexer **lst, t_lexer *newnode);
char	*clean_str(char *str, t_env *env);
char	*find_value(char *str, t_env *env);
size_t	handle_dollar(char *clean, char **tab, char *env_value);
size_t	count_dollar(char *str, t_env *env);
void	free_lexer(t_lexer **lexer);
void	print_lexer(t_lexer *lexer);
void	handle_backslash(char c, int *backslash);
t_lexer	*delete_empty_nodes(t_lexer *lexer);
int		strlen2(char *str, t_env *env, bool flag);
char	*find_value(char *str, t_env *env);
int		is_special_char(char c);
int		is_quote(char c, int backslash);
size_t	skip_word(const char *s, char c);

//PARSER

typedef struct s_parser_utils
{
	t_lexer			*lexer;
	t_lexer			*redirections;
	int				nb_of_redirections;
	struct s_parser	*parser;
}		t_parser_utils;

typedef struct s_parser
{
	char			**cmd;
	int				(*builtin)(t_env *, struct s_parser *);
	t_lexer			*redirections;
	int				nb_of_redirections;
	struct s_parser	*next;
	struct s_parser	*prev;	
}		t_parser;

void	parser_init(t_parser **parser, t_lexer **lexer, t_parser_utils *utils);
t_lexer	*find_redirection(t_lexer **lexer);
char	**build_command(t_lexer *lexer);
void	detach_from_lexer(t_lexer **lexer);
int		count_pipes(t_lexer *lexer);
int		count_nodes(t_lexer *lexer);
void	print_parser(t_parser *parser);
void	free_parser(t_parser **parser);

// BUILTINS

void	set_signal_action(void);
int		my_echo(t_env *env, struct s_parser *parser);
int		my_cd(t_env *env, struct s_parser *parser);
int		my_pwd(t_env *env, struct s_parser *parser);
int		my_export(t_env *env, struct s_parser *parser);
int		my_unset(t_env *env, struct s_parser *parser);
int		my_env(t_env *env, struct s_parser *parser);
int		my_exit(t_env *env, struct s_parser *parser);

#endif