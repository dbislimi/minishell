/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:24:13 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/22 16:24:26 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_env *env, char *type)
{
	int	i;

	if (!env)
		printf("env Vide\n");
	while (env)
	{
		i = 0;
		if (strcmp(type, "env") == 0)
			printf("%s=%s\n", env->name, env->value);
		else if (strcmp(type, "export") == 0)
		{
			if (env->value)
			{
				printf("declare -x %s=\"", env->name);
				while (env->value[i])
				{
					if (env->value[i] == '\"' || env->value[i] == '$'
						|| env->value[i] == '\\' || env->value[i] == '`'
						|| env->value[i] == '"')
						printf("\\");
					printf("%c", env->value[i]);
					i++;
				}
				printf("\"\n");
			}
			else
				printf("declare -x %s\n", env->name);
		}
		env = env->next;
	}
}
