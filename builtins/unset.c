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
	t_env	*old;
	t_env	*temp;
	int		i;

	temp = env;
	(void)parser;
	i = 1;
	while (env)
	{
		if (strcmp(parser->cmd[i], env->name) == 0)
		{
			old->next = env->next;
			free(env->name);
			free(env->value);
			free(env);
			env = temp;
			if (parser->cmd[i++ + 1] == NULL)
				return (1);
		}
		old = env;
		env = env->next;
	}
	return (0);
}
