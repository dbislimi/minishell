/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:12:57 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/05 19:06:40 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	len = strlen2(tab, env, 0);
	clean = ft_calloc(len + 1, sizeof(char));
	if (!clean)
		return (NULL);
	if (*tab == '"')
		++tab;
	while (i < len)
	{
		if (*tab == '\\' && is_special_char(*(tab + 1)))
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

char	*basic_clean(char *tab, t_env *env)
{
	char	*clean;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen2(tab, env, 1);
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
	else if (str[0] == '"')
		clean_str = clean(str, env);
	else
		clean_str = basic_clean(str, env);
	return (clean_str);
}
