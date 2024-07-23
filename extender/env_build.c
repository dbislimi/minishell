/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:38 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/23 18:22:52 by dbislimi         ###   ########.fr       */
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

static char	**split_for_env(char const *s, char c)
{
	char		**split;
	int			end;
	int			start;

	start = 0;
	split = malloc(sizeof(char *) * (3));
	if (!split)
		return (NULL);
	while (s[start] == c && s[start])
		start++;
	end = start + 1;
	while (s[end] != c && s[end])
		end++;
	split[0] = fill_str_with(s, start, end);
	start = end + 1;
	split[1] = fill_str_with(s, start, ft_strlen(s));
	split[2] = NULL;
	return (split);
}

t_env	*new_node(void *content)
{
	t_env	*new;
	char	**line;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	line = split_for_env(content, '=');
	new->variable = ft_strdup(line[0]);
	if (line[1])
		new->value = ft_strdup(line[1]);
	else
		new->value = ft_strdup("");
	new->next = NULL;
	free_tab(line);
	return (new);
}

t_env	*last_node(t_env *lst)
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

	if (*lst)
	{
		last = last_node(*lst);
		last->next = newnode;
	}
	else
		*lst = newnode;
}
