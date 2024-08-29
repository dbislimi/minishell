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

int	remove_env_var(t_env **env, t_env **old, t_env **temp)
{
	if (*old == NULL)
		*env = (*temp)->next;
	else
		(*old)->next = (*temp)->next;
	free((*temp)->name);
	free((*temp)->value);
	free(*temp);
	*temp = *env;
	if (*old == NULL)
		return (1);
	return (0);
}

int	my_unset(t_env **env, struct s_parser *parser)
{
	t_env	*old;
	t_env	*temp;
	int		i;

	temp = *env;
	old = NULL;
	i = 1;
	while (temp && parser->cmd[i])
	{
		if (strcmp(parser->cmd[i], temp->name) == 0 && strcmp(parser->cmd[i],
				"?") != 0)
		{
			if (remove_env_var(env, &old, &temp))
				continue ;
			if (parser->cmd[i++ + 1] == NULL)
			{
				add_node_char("?", "0", false, env);
				return (0);
			}
		}
		old = temp;
		temp = temp->next;
	}
	add_node_char("?", "0", false, env);
	return (0);
}
