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

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value && ft_strcmp(env->name, "?") != 0)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

t_env	*find_next_index(t_env *env, int index)
{
	t_env	*next;

	next = NULL;
	while (env)
	{
		if (env->index > index)
		{
			if (!next || env->index < next->index)
				next = env;
		}
		env = env->next;
	}
	return (next);
}

void	print_export(t_env *env)
{
	t_env	*temp_env;
	t_env	*tmp;
	int		temp;

	temp_env = env;
	while (env)
	{
		while (find_next_index(env, env->index))
		{
			tmp = find_next_index(env, env->index);
			printf("%s == %s\n", env->name, tmp->name);
			if (ft_strcmp(env->name, tmp->name) >= 0 && env->index < tmp->index)
			{
				printf("swap %s with %s\n", env->name, tmp->name);
				temp = env->index;
				env->index = tmp->index;
				tmp->index = temp;
				break ;
			}
			env = find_next_index(env, env->index);
		}
		if (!find_next_index(env, env->index))
			break ;
		env = temp_env;
	}
	print_export2(temp_env);
}

void	print_export2(t_env *env)
{
	int	i;

	i = 0;
	env = find_next_index(env, 0);
	while (env)
	{
		if (strcmp(env->name, "?") != 0)
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
				printf("%d\n", env->index);
			}
			printf("\n");
		}
		env = find_next_index(env, env->index);
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
