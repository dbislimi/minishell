/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:25:50 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:38:59 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_pwd(t_env *env, struct s_parser *parser)
{
	(void)env;
	(void)parser;
	printf("use of pwd\n");
	return (1);
}
