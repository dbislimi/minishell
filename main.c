/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:09:00 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/26 18:55:20 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	minishell(t_env **env)
{
	// t_lexer	*list;
	char	*str;
	char	**split;
	int	i;
	i = -1;
	(void)env;
	while (1)
	{
		str = readline("minishell> ");
		if (str == NULL)
			break ;
		split = ft_split_lexer(str);
		if (split == NULL)
			continue ;
		if (split)
		{
			while (split && split[++i])
				printf("s[%d] :%s(end)\n",i, split[i]);
			i = -1;
			
		}
		split = clean_tab(split, *env);
		printf("%d\n", count_words_lexer(str));
		if (split)
		{
			while (split && split[++i])
				printf("s[%d] :%s(end)\n",i, split[i]);
			i = -1;
			free_tab(split);
		}
		// lexer_init(&list, split);
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
	minishell(&env);
	envclear(&env);
}
