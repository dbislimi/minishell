/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:38 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/15 15:07:35 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_node(void *content)
{
	t_env	*new;
	char	**line;

	if (!content)
		return (0);
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	line = split_for_env(content);
	new->name = ft_strdup(line[0]);
	if (line[1] && ft_strlen(line[1]) > 0)
		new->value = ft_strdup(line[1]);
	else if (line[1] && ft_strlen(line[1]) == 0)
		new->value = ft_strdup("");
	else
		new->value = NULL;
	new->next = NULL;
	free_tab(line);
	return (new);
}

static t_env	*last_node(t_env *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
	}
	return (lst);
}

void	add_node(t_env **lst, t_env *newnode)
{
	int		i;
	t_env	*last;

	if (!newnode)
		return ;
	i = 0;
	while (newnode->name[i])
	{
		if ((i == 0 && ft_isdigit(newnode->name[i]))
			|| (!ft_isalnum(newnode->name[i]) && newnode->name[i] != '_'))
		{
			printf("minishell: export: « %s=%s » : not a valid identifier\n",
				newnode->name, newnode->value);
			return ;
		}
		i++;
	}
	i = env_edit(lst, newnode);
	if (!i && *lst)
	{
		last = last_node(*lst);
		last->next = newnode;
	}
	else if (!i)
		*lst = newnode;
}
