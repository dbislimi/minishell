/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:24:39 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:49 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_echo(t_env *env, struct s_parser *parser)
{
	(void)env;
	(void)parser;
	printf("use of echo\n");
	return (1);
}
