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
<<<<<<< HEAD
	printf("use of env\n");
	print_env(env);
=======
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
>>>>>>> 6696c3ff06f17ed57282e48a34e63306a9c25788
	return (1);
}
