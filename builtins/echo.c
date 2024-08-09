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

	i = 0;
	(void)env;
	(void)parser;
	printf("use of echo\n");
	while (parser->cmd[++i])
	{
		printf("%s", parser->cmd[i]);
	}
	printf("\n");
	return (1);
}
