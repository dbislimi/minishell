/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/02 19:54:29 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	minishell(t_env **env)
{
	//t_parser	*parser_list;
	t_lexer		*lexer_list;
	char		*str;

	lexer_list = NULL;
	str = NULL;
	while (1)
	{
		if (str != NULL)
			free(str);
		str = readline("minishell> ");
		if (str == NULL)
			break ;
		add_history(str);
		lexer_list = lexer(lexer_list, str, *env);
		if (lexer_list == NULL)
			continue ;
		parser(lexer_list);
		free_lexer(&lexer_list);
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
	minishell(&env);
	envclear(&env);
}
