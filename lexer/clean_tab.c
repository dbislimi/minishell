/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:12:57 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/27 20:31:35 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int tablen(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        ++i;
    return (i);
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

int	strlen2(char *str, t_env *env)
{
	int	i;
	char	*value;

	i = 0;
	if (*str == '"')
		++str;
	while (*str)
	{
		printf("TAB  :%s\n", str);
		if (*str == '\\')
			++str;
		else if (*str == '$')
		{
			value = find_value(++str, env);
			if (value != NULL)
				i += ft_strlen(value);
			while (ft_isalnum(*str))
				++str;
			continue ;
		}
		else if (*str == '"' || *str == '\0')
			break ;
		printf("TAB  :%s\n", str);
		++i;
		++str;
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
	++toclean;
	while (i < len - 2)
	{
		clean[i++] = *toclean++;
	}
	clean[i] = '\0';
	return (clean);
}

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

char	**clean_tab(char **tab, t_env *env)
{
	char	**clean_tab;
    int		i;
	int		len;

	i = -1;
	len = tablen(tab);
	clean_tab = malloc(sizeof(char *) * (len + 1));
	while (++i < len)
    {
		if (tab[i][0] == '\'')
			clean_tab[i] = simple_clean(tab[i]);
		else
			clean_tab[i] = clean(tab[i], env);
		if (clean_tab[i] == NULL)
			return (NULL);
	}
	clean_tab[i] = NULL;
	free_tab(tab);
	return (clean_tab);
}
