/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:38 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/12 19:50:11 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*fill_str_with(char const *s, int start, int end)
{
	char	*fill;
	int		i;

	i = 0;
	fill = malloc(sizeof(char) * (end - start + 1));
	if (!fill)
		return (NULL);
	while (start < end)
		fill[i++] = s[start++];
	fill[i] = 0;
	return (fill);
}
int	sizeofsplit(const char *s)
{
	const char	*equal;

	equal = ft_strchr(s, '=');
	if (equal == NULL)
		return (1);
	else
		return (2);
}

static char	**split_for_env(char const *s)
{
	char	**split;
	int		len;
	int		i;
	int		end;
	int		start;

	len = sizeofsplit(s);
	i = 0;
	start = 0;
	end = 1;
	split = malloc(sizeof(char *) * (len + 1));
	if (!split)
		return (NULL);
	while (s[end] && s[end] != '=')
				end++;
	while (i < len)
	{
		if (i != 0)
			while (s[end])
				end++;
		split[i++] = fill_str_with(s, start, end);
		start = end + 1;
	}
	split[i] = NULL;
	return (split);
}

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
	t_env	*last;

	if (!newnode)
		return ;
	if (env_edit(lst, newnode) == 1)
			return ;
	if (*lst)
	{
		last = last_node(*lst);
		last->next = newnode;
	}
	else
		*lst = newnode;
}
