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

	line = ft_strjoinf(line, "\033[1;34m", 1);
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
	{
		line = ft_strjoinf("\033[1;32m", tmp, 0);
		line = ft_strjoinf(line, "\033[0m:", 1);
	}
	tmp = find_value("PWD", env);
	if (tmp)
		line = get_pwd(line, tmp);
	line = ft_strjoinf(line, "\033[0m$ ", 1);
	tmp = readline(line);
	free(line);
	return (tmp);
}

void	minishell(t_env **env, int saved_stin, int saved_stout)
{
	t_parser	*parser_list;
	char		*str;
	char		*old;

	str = NULL;
	parser_list = NULL;
	while (1)
	{
		old = str;
		str = print_line(*env);
		if (str == NULL)
			break ;
		if (ft_strlen(str) != 0 && (!old || ft_strcmp(str, old) != 0))
			add_history(str);
		old = ft_free(old);
		lexer_parser(&parser_list, str, *env);
		if (parser_list == NULL)
			continue ;
		executor(env, parser_list);
		dup2(saved_stin, STDIN_FILENO);
		dup2(saved_stout, STDOUT_FILENO);
		free_parser(&parser_list);
	}
	free(old);
	free(str);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		saved_stin;
	int		saved_stout;

	env = NULL;
	saved_stin = dup(STDIN_FILENO);
	saved_stout = dup(STDOUT_FILENO);
	(void)av;
	if (ac > 1)
	{
		ft_fprintf(2, "minishell requires no arguments\n");
		exit(EXIT_FAILURE);
	}
	env_init(&env, envp);
	set_signal_action(sigint_handler);
	minishell(&env, saved_stin, saved_stout);
	envclear(&env);
}
