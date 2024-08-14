/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:26:10 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:39:03 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	my_unset(t_env *env, struct s_parser *parser)
{
	t_env	*tmp;

	(void)env;
	(void)parser;
	while (env)
	{
		if (strcmp(parser->cmd[1], env->name) == 0)
		{
			tmp->next = env->next;
			free(env->name);
			free(env->value);
			free(env);
			return (1);
		}
		tmp = env;
		env = env->next;
	}
	return (0);
}
