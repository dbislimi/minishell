/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:11:23 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:54 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_exit(t_env *env, struct s_parser *parser)
{
	int	exit_code;

	(void)env;
	exit_code = 0;
	if (parser->cmd[1])
	{
		exit_code = ft_atoi(parser->cmd[1]) % 256;
		if (exit_code < 0)
			exit_code = 256 + exit_code;
	}
	exit(exit_code);
	return (1);
}
