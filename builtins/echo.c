/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:24:39 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/10 16:28:30 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_echo(t_env *env, struct s_parser *parser)
{
	int	i;

	(void)env;
	i = 1;
	if (parser->cmd[1] && strcmp(parser->cmd[1], "-n") == 0)
		i++;
	while (parser->cmd[i])
	{
		ft_printf("%s", parser->cmd[i]);
		if (parser->cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!parser->cmd[1] || strcmp(parser->cmd[1], "-n") != 0)
		printf("\n");
	return (1);
}
