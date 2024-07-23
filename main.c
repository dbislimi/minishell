/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/22 17:31:13 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	sigint_handler(int signal)
{
	char	*str;
	
	if (signal == SIGINT)
	{
		printf("\n");
		str = readline("minishell> ");
	}
}

void	set_signal_action(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
}

void	minishell(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell> ");
		if (str == NULL)
			break ;
		add_history(str);
		free(str);
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
	minishell();
	envclear(&env);
}