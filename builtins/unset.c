/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:43:25 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 18:48:48 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    unset(char *variable, t_env *env)
{
    t_env   *temp;

    temp = NULL;
    while (env->next != NULL)
    {
        if (ft_strcmp(variable, env->next->variable) == 0)
        {
            temp = env->next->next;
            free(env->next->value);
            free(env->next->value);
            free(env->next);
            env->next = temp;
            break ;
        }
        env = env->next;
    }
}
