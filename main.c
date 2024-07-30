/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/30 19:12:53 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	minishell(t_env **env)
{
	t_lexer	*list;
	char	*str;

	list = NULL;
	str = NULL;
	while (1)
	{
		if (str != NULL)
			free(str);
		str = readline("minishell> ");
		if (str == NULL)
			break ;
		add_history(str);
		list = lexer(list, str, *env);
		if (list == NULL)
			continue ;
		free_lexer(&list);
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
