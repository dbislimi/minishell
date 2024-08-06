/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/06 18:44:57 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execution(t_parser *cmd, t_env *env)
{
	while (cmd)
	{
		if (cmd->builtin != NULL)
 			 cmd->builtin(env, cmd);
		cmd = cmd->next;
	}
}
void	lexer_parser(t_parser **parser, char *str, t_env *env)
{
	t_lexer		*lexer_list;

	lexer_list = NULL;
	lexer(&lexer_list, str, env);
	printf("debu\n");
	if (lexer_list == NULL)
		return ;
	parser_init(parser, lexer_list);
	free_lexer(&lexer_list);
	print_parser(*parser);
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
		str = readline("minishell> ");
		if (str == NULL)
			break ;
		add_history(str);
		lexer_parser(&parser_list, str, env);
		if (parser_list == NULL)
			continue ;
		execution(parser_list, env);
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
