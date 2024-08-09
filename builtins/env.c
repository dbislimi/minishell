/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:11:13 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/07 18:05:27 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_env(t_env *env, struct s_parser *parser)
{
	(void)parser;
	printf("use of env\n");
	print_env(env);
	return (1);
}
