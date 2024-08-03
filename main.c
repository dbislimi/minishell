/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/03 19:30:58 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	free_parser(t_parser **parser)
{
	t_parser	*temp;

	while (*parser)
	{
		temp = (*parser)->next;
		free_tab((*parser)->cmd);
		free_lexer(&(*parser)->redirections);
		free(*parser);
		*parser = temp;
	}
}

void	minishell(t_env **env)
{
	t_parser	*parser_list;
	t_lexer		*lexer_list;
	char		*str;

	parser_list = NULL;
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
		parser_init(&parser_list, lexer_list);
		free_lexer(&lexer_list);
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
	minishell(&env);
	envclear(&env);
}
