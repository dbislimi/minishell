/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:21:42 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:07:42 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	handle_dollar(char *clean, char **tab, char *env_value)
{
	if (env_value == NULL)
		return (0);
	ft_strcat(clean, env_value);
	++*tab;
	while (ft_isalnum(**tab) && **tab != '"')
		++*tab;
	return (ft_strlen(env_value));
}

size_t	count_dollar(char *str, t_env *env)
{
	char	*value;

	value = find_value(str, env);
	if (value == NULL)
		return (0);
	return (ft_strlen(value));
}

char	*find_value(char *str, t_env *env)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (ft_isalnum(str[j]) && str[j] != '"')
		++j;
	while (env)
	{
		i = ft_strlen(env->name);
		if (j > i)
			i = j;
		if (ft_strncmp(str, env->name, i) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	strlen2(char *str, t_env *env, bool flag)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (str[j] == '"')
		++j;
	while (str[j])
	{
		if (str[j] == '\\' && (flag == 1 || is_special_char(str[j + 1])))
			++j;
		else if (str[j] == '$')
		{
			i += count_dollar((str + ++j), env);
			while (ft_isalnum(str[j]))
				++j;
			continue ;
		}
		else if (str[j] == '"')
			break ;
		if (str[j] && ++j)
			++i;
	}
	return (i);
}

int	is_special_char(char c)
{
	return (c == '\\' || c == '$' || c == '"');
}
