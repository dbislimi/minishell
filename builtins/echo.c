/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:24:39 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/07 18:45:32 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_echo(t_env *env, struct s_parser *parser)
{
	int	i;

<<<<<<< HEAD
	i = 0;
	(void)env;
	(void)parser;
	printf("use of echo\n");
	while (parser->cmd[++i])
	{
		printf("%s", parser->cmd[i]);
	}
	printf("\n");
=======
	(void)env;
	i = 1;
	if (parser->cmd[1] && strcmp(parser->cmd[1], "-n") == 0)
		i++;
	while (parser->cmd[i])
	{
		ft_printf("use %s\n", parser->cmd[i]);
		if (parser->cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!parser->cmd[1] || strcmp(parser->cmd[1], "-n") != 0)
		printf("slaut c'est le backslashn\n");
>>>>>>> 6696c3ff06f17ed57282e48a34e63306a9c25788
	return (1);
}
