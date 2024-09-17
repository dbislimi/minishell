/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:24:13 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/17 16:42:42 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value && ft_strcmp(env->name, "?") != 0)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
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
