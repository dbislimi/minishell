/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:38 by dbislimi          #+#    #+#             */
/*   Updated: 2024/09/17 16:39:23 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_edit(t_env **lst, t_env *newnode)
{
	t_env	*tmp;

	newnode->index = max_index(*lst) + 1;
	tmp = *lst;
	while (tmp)
	{
		if (newnode && tmp->name && newnode->name && strcmp(tmp->name,
				newnode->name) == 0)
		{
			if (!tmp->value || (newnode->value && strcmp(tmp->value,
						newnode->value) != 0))
			{
				free(tmp->value);
				tmp->value = ft_strdup(newnode->value);
			}
			free(newnode->name);
			free(newnode->value);
			free(newnode);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
