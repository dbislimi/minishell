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

	while (env)
	{
		i = 0;
		if (strcmp(env->name, "?") == 0)
		{
			env = env->next;
			continue ;
		}
		else if (strcmp(type, "env") == 0)
			printf("%s=%s\n", env->name, env->value);
		else if (strcmp(type, "export") == 0)
			print_export(env, i);
		env = env->next;
	}
}

void	print_export(t_env *env, int i)
{
	printf("declare -x %s", env->name);
	if (env->value)
	{
		printf("=\"");
		while (env->value[i])
		{
			if (ft_strchr("$\"\\`", env->value[i]))
				printf("\\");
			print_brut_format(env->value[i]);
			i++;
		}
		printf("\"");
	}
	printf("\n");
}

void	print_brut_format(char c)
{
	if (c == '\n')
		printf("\\n");
	else if (c == '\t')
		printf("\\t");
	else if (c == '\v')
		printf("\\v");
	else if (c == '\b')
		printf("\\b");
	else if (c == '\r')
		printf("\\r");
	else if (c == '\f')
		printf("\\f");
	else
		printf("%c", c);
}
