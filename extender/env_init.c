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
		add_node(env, new, 1);
		++envp;
	}
	add_node_char("?", "0", false, env);
}

t_env	**dup_env(t_env *envp)
{
	t_env	**new;
	char	*buffer;

	new = malloc(sizeof(t_env *));
	*new = NULL;
	while (envp)
	{
		if (!envp->value)
			buffer = ft_strdup(envp->name);
		else
			buffer = ft_joinf("%s=%s", envp->name, envp->value);
		add_node(new, new_node(buffer), 1);
		free(buffer);
		envp = envp->next;
	}
	return (new);
}

void	check_delete(t_env **env, t_env **cpy)
{
	t_env	*temp;
	t_env	*tcpy;
	t_env	*old;
	int		found;

	temp = *env;
	old = NULL;
	while (temp)
	{
		found = 0;
		tcpy = *cpy;
		while (tcpy && !found)
		{
			if (strcmp(temp->name, tcpy->name) == 0)
				found = 1;
			tcpy = tcpy->next;
		}
		if (!found)
			if (remove_env_var(env, &old, &temp))
				continue ;
		old = temp;
		temp = temp->next;
	}
}

void	move_env(t_env **env, t_env **move)
{
	t_env	*tmove;
	t_env	*new;
	char	*buffer;

	tmove = *move;
	while (tmove)
	{
		if (!tmove->value)
			buffer = ft_joinf("%s", tmove->name);
		else
			buffer = ft_joinf("%s=%s", tmove->name, tmove->value);
		new = new_node(buffer);
		if (add_node(env, new, 1) == 2)
		{
			free(new->name);
		}
		free(buffer);
		tmove = tmove->next;
	}
	check_delete(env, move);
	envclear(move);
	free(move);
}
