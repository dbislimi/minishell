/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:12:57 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/30 18:27:33 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	strlen2(char *str, t_env *env)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (str[j] == '"')
		++j;
	while (str[j])
	{
		if (str[j] == '\\')
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

char	*simple_clean(char *toclean)
{
	char	*clean;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(toclean);
	clean = malloc(sizeof(char) * (len - 1));
	if (!clean)
		return (NULL);
	++toclean;
	while (i < len - 2)
	{
		clean[i++] = *toclean++;
	}
	clean[i] = '\0';
	return (clean);
}

char	*clean(char *tab, t_env *env)
{
	char	*clean;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen2(tab, env);
	clean = ft_calloc(len + 1, sizeof(char));
	if (!clean)
		return (NULL);
	if (*tab == '"')
		++tab;
	while (i < len)
	{
		if (*tab == '\\')
			++tab;
		else if (*tab == '$')
		{
			++tab;
			i += handle_dollar(clean, &tab, find_value(tab, env));
			continue ;
		}
		clean[i++] = *tab++;
	}
	clean[i] = '\0';
	return (clean);
}

char	*clean_str(char *str, t_env *env)
{
	char	*clean_str;

	clean_str = NULL;
	if (str[0] == '\'')
		clean_str = simple_clean(str);
	else
		clean_str = clean(str, env);
	return (clean_str);
}
