/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:18:35 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/22 16:39:29 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_init(t_env **env, char **envp)
{
	t_env	*new;

	while (envp && *envp)
	{
		new = new_node(*envp);
		add_node(env, new);
		++envp;
	}
}
