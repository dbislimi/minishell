/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/16 16:33:56 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	lexer_parser(t_parser **parser, char *str, t_env *env)
{
	t_lexer			*lexer_list;
	t_parser_utils	utils;

	lexer_list = NULL;
	lexer(&lexer_list, str, env);
	if (lexer_list == NULL)
		return ;
	utils.lexer = &lexer_list;
	utils.parser = parser;
	parser_init(parser, &lexer_list, &utils);
	if (DEBUG)
		print_parser(*parser);
}

static char	*get_pwd(char *line, char *pwd)
{
	char	*tmp;

	if (ft_strncmp(pwd, "/home/", 6) == 0)
	{
		line = ft_strjoinf(line, "~", 1);
		tmp = ft_strchr(pwd + 6, '/');
	}
	else
	{
		tmp = pwd + 1;
		line = ft_strjoinf(line, "/", 1);
	}
	line = ft_strjoinf(line, tmp, 1);
	return (line);
}

static char	*print_line(t_env *env)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = find_value("USER", env);
	if (tmp)
		line = ft_strjoinf(tmp, ":", 0);
	tmp = find_value("PWD", env);
	if (tmp)
		line = get_pwd(line, tmp);
	line = ft_strjoinf(line, "$ ", 1);
	tmp = readline(line);
	free(line);
	return (tmp);
}

void	minishell(t_env *env)
{
	t_parser	*parser_list;
	char		*str;

	str = NULL;
	parser_list = NULL;
	while (1)
	{
		if (str != NULL)
			free(str);
		str = print_line(env);
		if (str == NULL)
			break ;
		if (ft_strlen(str) != 0)
			add_history(str);
		lexer_parser(&parser_list, str, env);
		if (parser_list == NULL)
			continue ;
		executor(&env, parser_list);
		free_parser(&parser_list);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	env = NULL;
	if (ac > 1)
	{
		write(2, "minishell requires no arguments\n", 33);
		exit(EXIT_FAILURE);
	}
	env_init(&env, envp);
	set_signal_action();
	minishell(env);
	envclear(&env);
}
