/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:12:57 by dbislimi          #+#    #+#             */
/*   Updated: 2024/08/06 19:05:42 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*simple_clean(char *toclean)
{
	char	*clean_str;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(toclean);
	clean_str = malloc(sizeof(char) * (len - 1));
	if (!clean_str)
		return (NULL);
	++toclean;
	while (i < len - 2)
		clean_str[i++] = *toclean++;
	clean_str[i] = '\0';
	return (clean_str);
}

static char	*clean(char *tab, t_env *env)
{
	char	*clean_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen2(tab, env, 0);
	clean_str = ft_calloc(len + 1, sizeof(char));
	if (!clean_str)
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
			i += handle_dollar(clean_str, &tab, find_value(tab, env));
			continue ;
		}
		clean_str[i++] = *tab++;
	}
	clean_str[i] = '\0';
	return (clean_str);
}

static char	*basic_clean(char *tab, t_env *env)
{
	char	*clean_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen2(tab, env, 1);
	clean_str = ft_calloc(len + 1, sizeof(char));
	if (!clean_str)
		return (NULL);
	while (i < len)
	{
		if (*tab == '\\')
			++tab;
		else if (*tab == '$')
		{
			++tab;
			i += handle_dollar(clean_str, &tab, find_value(tab, env));
			continue ;
		}
		clean_str[i++] = *tab++;
	}
	clean_str[i] = '\0';
	return (clean_str);
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
