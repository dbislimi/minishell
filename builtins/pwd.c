/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:11:53 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 17:17:35 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_env *env)
{
	while(env)
	{
        if (strcmp(env->name, "PWD") == 0) 
		{
			printf("%s\n", env->value);
			break ;
		}
		env = env->next;
    }
}
